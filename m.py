import os
import re
import subprocess
import threading
import telebot
import logging
import random
import pytz
import requests
import ipaddress
from datetime import datetime, timedelta
from telebot.types import ReplyKeyboardMarkup, KeyboardButton
from pymongo import MongoClient

# Constants
MONGO_URI = "mongodb+srv://lm6000k:IBRSupreme@ibrdata.uo83r.mongodb.net/"
DB_NAME = "action"
COLLECTION_NAME = "action"
TOKEN = "7267969157:AAFBW9fqZYa1kMnAB9CerIxWQnJ0-6c7Wns"
KOLKATA_TZ = pytz.timezone('Asia/Kolkata')
AUTHORIZED_USERS = [6800732852]
MAX_DURATION = 600  # Maximum duration in seconds

# Initialize MongoDB
client = MongoClient(MONGO_URI)
db = client[DB_NAME]
actions_collection = db[COLLECTION_NAME]

# Initialize the bot
bot = telebot.TeleBot(TOKEN)

# Logging setup
logging.basicConfig(filename='bot_actions.log', level=logging.INFO, 
                    format='%(asctime)s - %(message)s')

# Global variables
authorized_users = {}
processes = {}
user_modes = {}
supporter_users = {}

# Utility Functions
def is_valid_ip(ip):
    """Check if the provided IP address is valid."""
    try:
        ipaddress.ip_address(ip)
        return True
    except ValueError:
        return False

def is_valid_port(port):
    """Check if the provided port is valid."""
    return 1 <= int(port) <= 65535

def is_valid_duration(duration):
    """Check if the provided duration is valid."""
    return 1 <= int(duration) <= MAX_DURATION

def notify_admins(user_id, username):
    """Notify admins about a new authorization request."""
    message = (
        "🔔 ||*New Authorization Request!*||\n\n"
        "👤 **User**: @{username}\n"
        "🆔 *ID*: {user_id}\n\n"
        "🕒 ||Request Time||: _Pending Approval_\n\n"
        "💡 Use `/approve <user_id>` to authorize.")
    for admin_id in AUTHORIZED_USERS:
        bot.send_message(admin_id, message, parse_mode='Markdown')

# Database Operations
def authorize_user(user_id, expire_time):
    """Authorize a user and set expiration time."""
    expire_time_utc = expire_time.astimezone(pytz.utc)
    actions_collection.update_one(
        {'user_id': user_id},
        {'$set': {'status': 'authorized', 'expire_time': expire_time_utc}},
        upsert=True
    )

def load_authorizations():
    """Load all authorized users from MongoDB."""
    global authorized_users
    authorized_users = {}
    users = actions_collection.find({"status": "authorized"})
    for user in users:
        user_id = str(user['user_id'])
        expire_time_utc = user.get('expire_time', datetime.utcnow())
        expire_time_kolkata = expire_time_utc.astimezone(KOLKATA_TZ)
        user['expire_time'] = expire_time_kolkata
        authorized_users[user_id] = user

def save_authorizations():
    """Save all authorized users to MongoDB."""
    for user_id, info in authorized_users.items():
        expire_time_utc = info['expire_time'].astimezone(pytz.utc)
        actions_collection.update_one(
            {'user_id': user_id}, 
            {'$set': {'status': info['status'], 'expire_time': expire_time_utc}},
            upsert=True
        )

# Bot Handlers
@bot.message_handler(commands=['start'])
def send_welcome(message):
    """Send a welcome message with options for manual or auto mode."""
    markup = ReplyKeyboardMarkup(one_time_keyboard=True, resize_keyboard=True)
    markup.add(KeyboardButton('Manual Mode'), KeyboardButton('Auto Mode'))
    welcome_text = (
    "👋 *Welcome to Action Bot!*\n\n"
    "I help you manage actions efficiently. 🚀\n\n"
    "🔹 **Modes**:\n"
    "1. _Manual Mode_: Enter `IP`, `Port`, and `Duration`.\n"
    "2. _Auto Mode_: Enter `IP` and `Port`; duration is randomly assigned.\n\n"
    "🔹 **Stop Actions**:\n"
    "Type ||stop all|| to halt all operations.\n\n"
    "🔐 Only _authorized users_ can access this bot. Type `/auth` to request access."
    )
    bot.reply_to(message, welcome_text, parse_mode='Markdown', reply_markup=markup)

  
@bot.message_handler(func=lambda message: True)
def handle_message(message):
    user_id = message.from_user.id
    chat_type = message.chat.type

    # Skip authorization check if the user is in the AUTHORIZED_USERS list
    if chat_type == 'private' and user_id not in AUTHORIZED_USERS and not is_authorized(user_id):
        bot.reply_to(message, '⛔ *You are not authorized to use this bot.* Please send /auth to request access. 🤔\n\n_This bot was made by Ibr._', parse_mode='Markdown')
        return

    text = message.text.strip()

    # Regex to match "<ip> <port> <duration>"
    match = re.match(r"(\b\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}\b)\s(\d{1,5})\s(\d{1,4})", text)

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

        # Respond to the user that the action is starting
        bot.reply_to(
        message,
        (
        "✅ *Action Successfully Initiated!* 🚀\n\n"
        "🌐 **Target Details**:\n"
        "   - 📡 *IP Address*: `||{ip}||`\n"
        "   - 🔗 *Port*: `{port}`\n"
        "   - ⏱️ *Duration*: `{duration} seconds`\n\n"
        "⚙️ _Processing your request..._\n\n"
        "💡||Your request is queued; Wait till finish||.\n\n"
        "_Developed with 💻 by Ibr._"
        ),
        parse_mode='Markdown'
        ) 

        # Start the action
        run_action(user_id, message, ip, port, int(duration))
    else:
        bot.reply_to(
        message,
        (
        "🚨 *Oops! Something went wrong.*\n\n"
        "📌 **Correct Format**:\n"
        "`<ip> <port> <duration>`\n\n"
        "💡 **Example**:\n"
        "`10.0.0.1 44544 10`\n\n"
        "💾 Ensure:\n"
        "1️⃣ *IP is valid*.\n"
        "2️⃣ *Port is within range (1-65535)*.\n"
        "3️⃣ *Duration is between 1 and 600 seconds*.\n\n"
        ),
        parse_mode='Markdown'
        )


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
def is_authorized(user_id):
    """Check if a user is authorized."""
    user = actions_collection.find_one({'user_id': user_id})
    if user and user['status'] == 'authorized':
        now = datetime.now(KOLKATA_TZ)
        expire_time = user['expire_time'].astimezone(KOLKATA_TZ)
        if now < expire_time:
            return True
        actions_collection.update_one({'user_id': user_id}, {'$set': {'status': 'expired'}})
    return False

# Function to set or get the thread value
def get_thread_value(user_id):
    """Retrieve the user's thread value or default to random if not set."""
    user_settings = actions_collection.find_one({'user_id': user_id})
    if user_settings and 'thread_value' in user_settings:
        return user_settings['thread_value']
    return random.choice([40, 50, 80, 140])

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
        bot.reply_to(
            message,
            "❌ Invalid command format or value!\n\n"
            "Use `/setthread <value>` to set your thread value.\n"
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


# Updated run_action function
def run_action(user_id, message, ip, port, duration):
    """
    Run an action, save its process with user ID, and monitor it.
    """
    #thread_value = random.choice([40, 50, 80, 140])
    thread_value = current_value = get_thread_value(user_id)
    logging.info(f"User {user_id} started action on IP {ip}, Port {port}, Duration {duration}s")

    # Build the full command
    full_command = f"./action {ip} {port} {duration} {thread_value}"

    # Start the action command as a non-blocking subprocess
    process = subprocess.Popen(full_command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    # Save the process with user ID in the global dictionary
    processes[process.pid] = {"process": process, "user_id": user_id}

    # Notify the user
    bot.reply_to(message, f"🎉 *Socket value is {thread_value}*", parse_mode='Markdown')

    # Monitor the process in a separate thread
    threading.Thread(target=check_process_status, args=(message, process, ip, port, duration)).start()


# Updated stop_user_actions function
@bot.message_handler(commands=['stop'])
def stop_user_actions(message):
    """
    Allow a user to stop their own actions without needing to specify their user ID.
    """
    try:
        user_id = message.from_user.id
        user_processes = [pid for pid, data in processes.items() if data['user_id'] == user_id]

        if not user_processes:
            bot.reply_to(message, f"🤔 *No active actions found for your account.*", parse_mode='Markdown')
            return

        for pid in user_processes:
            process_data = processes.pop(pid, None)
            if process_data:
                process_data['process'].terminate()
                process_data['process'].wait()

        bot.reply_to(message, f"🛑 *All your actions have been stopped!* 🙅‍♂️", parse_mode='Markdown')

    except Exception as e:
        logging.error(f"Error in stop_user_actions: {e}")
        bot.reply_to(message, "❌ *An error occurred while trying to stop your actions.*", parse_mode='Markdown')


def check_process_status(message, process, ip, port, duration):
    try:
        # Wait for the specified duration
        process.wait(timeout=duration)
    except subprocess.TimeoutExpired:
        # If the process is still running after the duration, terminate it
        process.terminate()
        try:
            process.wait(timeout=5)  # Allow 5 seconds for graceful termination
        except subprocess.TimeoutExpired:
            process.kill()  # Force kill if still not terminated
            process.wait()

    # Remove the process from the active list after completion
    processes.pop(process.pid, None)

    # Create the button markup for the response
    markup = ReplyKeyboardMarkup(one_time_keyboard=True, resize_keyboard=True)
    manual_button = KeyboardButton('Manual Mode')
    auto_button = KeyboardButton('Auto Mode')
    markup.add(manual_button, auto_button)

    # Send completion message to the user
    bot.reply_to(message, (
        f"✅ *Action completed successfully!* 🎉\n\n"
        f"🌐 *Target IP:* `{ip}`\n"
        f"🔌 *Port:* `{port}`\n"
        f"⏱ *Duration:* `{duration} seconds`\n\n"
        "💡 *Need more help?* Just send me another request, I'm here to assist! 🤗\n\n"
        "_This bot was made by Ibr._"
    ), parse_mode='Markdown', reply_markup=markup)

def stop_all_actions(message):
    if processes:
        for pid, process in list(processes.items()):
            process.terminate()
            process.wait()
            processes.pop(pid, None)
        bot.reply_to(message, "🛑 *All actions have been stopped!* 🙅‍♂️", parse_mode='Markdown')
    else:
        bot.reply_to(message, "🤔 *No ongoing actions to stop.*", parse_mode='Markdown')


# Periodic Tasks
def check_expired_users():
    """Periodically check for expired users and update their status."""
    now_utc = datetime.now(KOLKATA_TZ).astimezone(pytz.utc)
    expired_users = actions_collection.find({'status': 'authorized', 'expire_time': {'$lte': now_utc}})
    for user in expired_users:
        actions_collection.update_one({'user_id': user['user_id']}, {'$set': {'status': 'expired'}})
    threading.Timer(900, check_expired_users).start()  # Run every 15 minutes

# Start the Bot
if __name__ == '__main__':
    logging.info("Starting the bot...")
    load_authorizations()
    check_expired_users()
    bot.polling(none_stop=True)
