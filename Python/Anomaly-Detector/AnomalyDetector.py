"""
Topic: Data Parsing & Regular Expressions (RegEx)
Problem: System administrators receive massive text files containing server logs. 
Manually finding which IP addresses are causing crashes (500-level errors) is impossible.
Approach: We use RegEx to cleanly extract the IP address and HTTP status code from raw text.
We then use Python's built-in collections.Counter to instantly aggregate the data and find 
the worst-offending network addresses in O(N) time.
"""

import re
from collections import Counter

def analyze_logs(log_data):
    # Regex pattern to grab an IP address and a 3-digit status code
    pattern = re.compile(r"(\d+\.\d+\.\d+\.\d+).*HTTP/1\.1\" (\d{3})")
    
    error_ips = []
    print("\n\033[36mScanning log stream for 500-level anomalies...\033[0m")
    
    for line in log_data:
        match = pattern.search(line)
        if match:
            ip = match.group(1)
            status = match.group(2)
            
            # If the status code starts with '5' (Server Error)
            if status.startswith("5"):
                error_ips.append(ip)
                
    if not error_ips:
        print("\033[32mSystem Healthy: No critical server errors detected.\033[0m")
        return
        
    print("\033[33m\nAnomaly Report Generated:\033[0m")
    ip_counts = Counter(error_ips)
    for ip, count in ip_counts.most_common():
        print(f"  \033[1m{ip}\033[0m triggered \033[31m{count}\033[0m critical errors.")

if __name__ == "__main__":
    print("\033[1m\n--- Network Anomaly Detector ---\033[0m")
    print("Paste your server logs below. Type 'ANALYZE' on a new line to process.")
    
    # Mock data to help the user test it easily
    print("\033[90m(Try pasting this format: 192.168.1.1 - \"GET /api\" HTTP/1.1\" 500)\033[0m")
    
    raw_logs = []
    while True:
        try:
            line = input("> ")
            if line.strip().upper() == 'ANALYZE':
                break
            raw_logs.append(line)
        except EOFError:
            break
            
    analyze_logs(raw_logs)