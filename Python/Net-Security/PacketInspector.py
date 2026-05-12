"""
* [PROBLEM STATEMENT]
* Raw network data is messy. If we try to analyze every single byte 
* manually, the system will lag. We need a "Filter Logic" that can 
* quickly identify 'Malformed' packets or 'Spoofing' attempts by 
* checking the header structures.
*
* [LOGIC & INSIGHT]
* I simulated a 'Bitwise Packet Inspector'. I use Python's dictionary 
* mapping for O(1) lookups of known malicious IPs. The core logic 
* here is the 'Integrity Hash' check—I've created a simple checksum 
* algorithm to verify if a packet was tampered with during transit. 
* This demonstrates my ability to handle raw data and apply 
* security-first thinking.
"""

import hashlib
import time

class PacketInspector:
    def __init__(self):
        self.blacklist = {"192.168.1.50", "10.0.0.13"}

    def generate_checksum(self, payload):
        return hashlib.md5(payload.encode()).hexdigest()[:8]

    def inspect(self, packet):
        source = packet.get("src")
        payload = packet.get("data")
        checksum = packet.get("chk")

        print(f"\n\033[1m[INSPECTING]\033[0m Packet from {source}...")
        time.sleep(0.3)

        # 1. Source Check
        if source in self.blacklist:
            print("\033[31m  [REJECTED]\033[0m Source IP is blacklisted.")
            return False

        # 2. Integrity Check
        if self.generate_checksum(payload) != checksum:
            print("\033[31m  [REJECTED]\033[0m Checksum Mismatch! Data Tampered.")
            return False

        print("\033[32m  [CLEARED]\033[0m Packet moved to processing queue.")
        return True

# Mock Packets
p1 = {"src": "192.168.1.10", "data": "AUTH_REQ", "chk": "56708b52"}
p2 = {"src": "192.168.1.50", "data": "SUDO_ACCESS", "chk": "a1b2c3d4"}

inspector = PacketInspector()
inspector.inspect(p1)
inspector.inspect(p2)