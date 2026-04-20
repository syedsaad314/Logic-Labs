"""
Problem: Static passwords can be keylogged or stolen. We need a secondary layer of authentication 
that changes continuously and cannot be reused.
Logic: Time-Based OTP. Both the server and the client's app share a secret key. They both 
take the current UNIX timestamp, divide it by 30 (so it changes every 30 seconds), combine it 
with the secret, and hash it. If the server's generated 6-digit pin matches the user's, access is granted.
"""

import time
import hashlib

class Authenticator:
    def __init__(self, secret_key):
        self.secret_key = secret_key
        self.interval = 30 # Code rotates every 30 seconds

    def generate_code(self):
        # 1. Get current UNIX time
        current_time = int(time.time())
        
        # 2. Divide by interval to get a time counter that stays the same for 30s
        time_counter = current_time // self.interval
        
        # 3. Combine secret and time counter
        payload = f"{self.secret_key}-{time_counter}"
        
        # 4. Hash the payload
        hash_digest = hashlib.sha1(payload.encode('utf-8')).hexdigest()
        
        # 5. Extract a 6-digit integer from the hash
        # (Simplified extraction for demonstration)
        numeric_hash = int(hash_digest, 16)
        six_digit_code = str(numeric_hash)[-6:]
        
        # Calculate time remaining for UI
        time_remaining = self.interval - (current_time % self.interval)
        
        return six_digit_code, time_remaining

if __name__ == "__main__":
    print("\033[1m\n--- 2FA Token Generator (TOTP) ---\033[0m")
    
    user_secret = input("\033[90mEnter a secure master seed (e.g., 'MyServerSecret99'): \033[0m")
    auth = Authenticator(user_secret)
    
    print("\n\033[36m[Syncing cryptographic clock...]\033[0m\n")
    
    try:
        last_code = ""
        while True:
            code, ttl = auth.generate_code()
            
            # Only print if the code changed to avoid terminal spam
            if code != last_code:
                print(f"\033[1m  Current Auth Token:\033[0m \033[32m{code}\033[0m")
                last_code = code
                
            # Overwrite the same line for the countdown timer
            print(f"\r  \033[90mToken expires in: {ttl:02d}s\033[0m", end="")
            time.sleep(1)
            
    except KeyboardInterrupt:
        print("\n\n\033[90mTerminating authenticator process...\033[0m")