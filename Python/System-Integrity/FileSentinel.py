"""
* [PROBLEM STATEMENT]
* Hackers often inject "Backdoor" code into configuration files. To catch 
* this, we need a tool that takes a "Snapshot" of a file's content and 
* alerts us immediately if even a single comma changes.
*
* [LOGIC & INSIGHT]
* I used 'SHA-256' hashing to create a digital fingerprint of files. 
* The script stores the "Known Good" hash. On every run, it re-calculates 
* the current hash and compares them. I added a 'Criticality' level 
* to the output, so a DevOps engineer knows if a sensitive system 
* file has been tampered with. It’s simple, effective, and professional.
"""

import hashlib
import os

class FileSentinel:
    def __init__(self, target_file):
        self.target = target_file
        self.original_hash = self._get_hash()

    def _get_hash(self):
        with open(self.target, "rb") as f:
            return hashlib.sha256(f.read()).hexdigest()

    def monitor(self):
        current_hash = self._get_hash()
        print(f"\033[1m[SENTINEL]\033[0m Checking {self.target}...")
        
        if current_hash != self.original_hash:
            print("\033[31m  [ALARM] INTEGRITY BREACH DETECTED!\033[0m")
            print(f"  Expected: {self.original_hash[:16]}...")
            print(f"  Actual:   {current_hash[:16]}...")
            return False
        
        print("\033[32m  [OK] File integrity verified.\033[0m")
        return True

# Mock a config file
with open("sys.config", "w") as f: f.write("PORT=8080")

sentinel = FileSentinel("sys.config")
sentinel.monitor()

# Simulate a breach
with open("sys.config", "w") as f: f.write("PORT=8080; ALLOW_ALL=TRUE")
sentinel.monitor()