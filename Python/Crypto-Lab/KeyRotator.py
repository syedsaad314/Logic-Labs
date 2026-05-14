"""
* [PROBLEM STATEMENT]
* Using a fixed encryption key for months is a massive security risk. 
* If the key is leaked, all past data is compromised. We need a system 
* that "Rotates" keys by adding a unique 'Salt' to each session, 
* ensuring that the same password never looks the same twice in the DB.
*
* [LOGIC & INSIGHT]
* I used the 'hashlib' library to build a session-based hasher. 
* I personally designed the logic to take a 'Master Secret' and 
* combine it with a random 'Salt'. Even if an attacker knows the 
* algorithm, without the unique salt, they can't reverse the hash. 
* I've also formatted the output to show the 'Hex-Digest'—perfect 
* for storing in a MongoDB or SQL database.
"""

import hashlib
import secrets

class KeyRotator:
    def __init__(self, master_secret):
        self.master_secret = master_secret

    def generate_session_key(self, user_id):
        # Generate a cryptographically secure random salt
        salt = secrets.token_hex(8)
        
        # Combine everything and hash
        raw_data = f"{self.master_secret}{user_id}{salt}"
        secure_key = hashlib.sha256(raw_data.encode()).hexdigest()
        
        print(f"\033[1m[SESSION_GEN]\033[0m User: {user_id}")
        print(f"  \033[36mSalt:\033[0m {salt}")
        print(f"  \033[32mHash:\033[0m {secure_key[:24]}...")
        
        return {"key": secure_key, "salt": salt}

# Logic Lab Execution
rotator = KeyRotator("UBIT_BACKEND_SECRET_2026")
session_1 = rotator.generate_session_key("Saad_Admin")
session_2 = rotator.generate_session_key("Saad_Admin") 

# Notice how the hash is completely different even for the same user!