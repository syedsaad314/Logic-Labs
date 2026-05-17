"""
* [PROBLEM STATEMENT]
* Without rate limiting, a malicious script can hit our MERN backend 
* 10,000 times a second, crashing the database and causing a Denial 
* of Service (DDoS). 
*
* [LOGIC & INSIGHT]
* I built a custom Python Decorator wrapper. By simply adding `@rate_limit` 
* above any API route function, it automatically tracks how many times an 
* IP address has accessed it within a time window. It intercepts and 
* blocks the request entirely if the threshold is exceeded, keeping the 
* core function logic clean and focused strictly on business logic.
"""

import time
from functools import wraps

class APISecurity:
    def __init__(self):
        self.access_logs = {}

    def rate_limit(self, max_requests, time_window_seconds):
        def decorator(func):
            @wraps(func)
            def wrapper(ip_address, *args, **kwargs):
                current_time = time.time()
                
                # Initialize or clean old logs
                if ip_address not in self.access_logs:
                    self.access_logs[ip_address] = []
                
                # Remove timestamps older than the time window
                self.access_logs[ip_address] = [
                    t for t in self.access_logs[ip_address] 
                    if current_time - t < time_window_seconds
                ]

                # Check constraint
                if len(self.access_logs[ip_address]) >= max_requests:
                    print(f"  \033[41m\033[30m [HTTP 429] \033[0m IP {ip_address} BLOCKED. Rate limit exceeded.")
                    return {"status": 429, "error": "Too Many Requests"}

                # Allow request
                self.access_logs[ip_address].append(current_time)
                print(f"  \033[32m[HTTP 200]\033[0m IP {ip_address} Authorized. Executing logic...")
                return func(ip_address, *args, **kwargs)
            return wrapper
        return decorator

security_engine = APISecurity()

# The Decorator in Action
@security_engine.rate_limit(max_requests=3, time_window_seconds=10)
def fetch_user_data(ip_address):
    return {"data": "Secure Database Information Loaded"}

print("\033[1m--- INITIATING TRAFFIC SPIKE SIMULATION ---\033[0m")
client_ip = "192.168.1.105"

# Simulating a rapid loop of 5 requests (Only 3 should pass)
for i in range(5):
    fetch_user_data(client_ip)