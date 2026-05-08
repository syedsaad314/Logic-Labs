"""
* System: Solar-Flare Data Core
* Engine: SQLite3 (Native Python)
* Purpose: Create a local, persistent database to store and analyze security logs.
"""
import sqlite3
import random
from datetime import datetime, timedelta

# 1. Connect to Database (creates the file 'solar_flare.db' automatically)
conn = sqlite3.connect("solar_flare.db")
cursor = conn.cursor()

print("\033[1m\n--- Database Engine Initialized ---\033[0m")

# 2. Build the Schema (The structure of our data)
cursor.execute('''
    CREATE TABLE IF NOT EXISTS security_logs (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        timestamp TEXT,
        user_role TEXT,
        action TEXT,
        status TEXT
    )
''')

# Clear old data so we get a fresh run every time we test it
cursor.execute('DELETE FROM security_logs')

# 3. Generate Synthetic Data
roles = ["ADMIN", "GUEST", "UNKNOWN_BOT"]
actions = ["READ_LOGS", "REBOOT_SERVER", "EDIT_USERS"]

print("  \033[36m[System]\033[0m Injecting 50 security events into the database...")

for i in range(50):
    # Generate a random time in the last 24 hours
    time_offset = timedelta(minutes=random.randint(1, 1440))
    log_time = (datetime.now() - time_offset).strftime("%Y-%m-%d %H:%M:%S")
    
    role = random.choice(roles)
    action = random.choice(actions)
    
    # Logic constraint: Only ADMINs get GRANTED for REBOOT or EDIT. 
    if role == "ADMIN":
        status = "GRANTED"
    elif role == "GUEST" and action == "READ_LOGS":
        status = "GRANTED"
    else:
        status = "DENIED"

    # Insert into the database
    cursor.execute('''
        INSERT INTO security_logs (timestamp, user_role, action, status)
        VALUES (?, ?, ?, ?)
    ''', (log_time, role, action, status))

# Save the data permanently
conn.commit()

# 4. Data Analytics (Querying the DB for threats)
print("\n\033[1m--- Threat Analysis Report ---\033[0m")

# Query: Find all DENIED reboot attempts by non-admins
cursor.execute('''
    SELECT timestamp, user_role FROM security_logs 
    WHERE action = 'REBOOT_SERVER' AND status = 'DENIED'
    ORDER BY timestamp DESC
''')

threats = cursor.fetchall()

if threats:
    print(f"  \033[31m[CRITICAL ALERT]\033[0m Detected {len(threats)} unauthorized server reboot attempts:")
    for threat in threats:
        print(f"    -> Time: {threat[0]} | Origin Role: {threat[1]}")
else:
    print("  \033[32m[SAFE]\033[0m No unauthorized reboot attempts detected in the timeframe.")

# Close connection
conn.close()