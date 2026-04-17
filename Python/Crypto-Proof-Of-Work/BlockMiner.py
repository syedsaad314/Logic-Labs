"""
Problem: In decentralized systems (like Blockchain), how do we prevent users from spamming 
fake data blocks instantly?
Logic: Proof of Work (Mining). We force the computer to spend raw CPU power to solve a math 
puzzle. It repeatedly hashes the block's data combined with a random number (Nonce) until the 
resulting hash starts with a specific number of zeroes (the Difficulty).
"""

import hashlib
import time

def mine_block():
    print("\033[1m\n--- Cryptographic Proof-Of-Work Miner ---\033[0m")
    print("\033[90mSimulating the core consensus algorithm of distributed ledgers.\033[0m\n")

    while True:
        try:
            data = input("\033[1mBlock Data (e.g., 'Tx: A sends B $50') > \033[0m").strip()
            if data.lower() == 'exit': break
            
            diff_input = input("\033[1mMining Difficulty (1-6 zeroes) > \033[0m").strip()
            difficulty = int(diff_input)
            target_prefix = '0' * difficulty
            
            nonce = 0
            hash_result = ""
            
            print(f"\n  \033[90mMining started... Target hash must start with: '{target_prefix}'\033[0m")
            start_time = time.time()
            
            while True:
                # Combine data and nonce, then SHA-256 hash it
                text = f"{data}{nonce}"
                hash_result = hashlib.sha256(text.encode('utf-8')).hexdigest()
                
                if hash_result.startswith(target_prefix):
                    break
                    
                nonce += 1
                
                # Terminal animation for visual feedback (every 100k hashes)
                if nonce % 100000 == 0:
                    print(f"  \033[33mAttempt {nonce}:\033[0m {hash_result}")
            
            end_time = time.time()
            time_taken = round(end_time - start_time, 2)
            
            print(f"\n  \033[32m✓ Block Mined Successfully!\033[0m")
            print(f"  \033[1mNonce Found:\033[0m {nonce}")
            print(f"  \033[1mBlock Hash:\033[0m  {hash_result}")
            print(f"  \033[90mTime Elapsed:  {time_taken} seconds\033[0m\n")

        except ValueError:
            print("  \033[31mDifficulty must be an integer.\033[0m\n")
        except KeyboardInterrupt:
            break

if __name__ == "__main__":
    mine_block()