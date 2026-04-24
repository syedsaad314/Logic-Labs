"""
Problem (The Commons): Checking if a username or email is already taken in a database of 
10 billion users is painfully slow and costs massive server resources. 
Logic: The Bloom Filter. Instead of searching a massive database, we hash the input 
multiple times and flip bits in a tiny array. It tells us with 100% certainty if a username 
is *available*, and with high probability if it is *taken*, saving 99% of database queries.
"""

import hashlib
import time

class GhostSet:
    def __init__(self, size=50, hash_count=3):
        self.size = size
        self.hash_count = hash_count
        self.bit_array = [False] * size

    def _get_hashes(self, item):
        indices = []
        for i in range(self.hash_count):
            hash_str = hashlib.md5(f"{item}salt{i}".encode('utf-8')).hexdigest()
            indices.append(int(hash_str, 16) % self.size)
        return indices

    def register(self, item):
        for idx in self._get_hashes(item):
            self.bit_array[idx] = True

    def check(self, item):
        for idx in self._get_hashes(item):
            if not self.bit_array[idx]:
                return False # 100% definitely not in the system
        return True # Probably in the system

if __name__ == "__main__":
    print("\033[1m\n--- GhostSet Verifier (Bloom Filter Engine) ---\033[0m")
    print("\033[90mWe are simulating a massive database of taken usernames.\033[0m")
    
    db = GhostSet()
    taken_users = ["saad", "admin", "root", "test", "user123"]
    for u in taken_users: db.register(u)
    
    print(f"\033[90mPre-loaded taken names: {', '.join(taken_users)}\033[0m\n")

    while True:
        try:
            query = input("\033[1mEnter username to check (or 'exit') > \033[0m").strip().lower()
            if query == 'exit': break
            
            print("  \033[36m[Processing]\033[0m Hashing query against bit array...")
            time.sleep(0.5) # Simulating processing
            
            if db.check(query):
                print(f"  \033[33m[!] WARNING:\033[0m '{query}' is PROBABLY taken. Fallback to slow DB check required.\n")
            else:
                print(f"  \033[32m[✓] CLEAR:\033[0m '{query}' is 100% available. No DB query needed!\n")
                
        except KeyboardInterrupt:
            break