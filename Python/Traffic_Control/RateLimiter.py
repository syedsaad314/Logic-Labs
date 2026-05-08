"""
Problem: A malicious user or bot tries to refresh the dashboard 1,000 times a second, crashing our server (DDoS).
Logic: The Token Bucket / Timestamp algorithm. We track how many requests an IP 
makes within a specific time window. If they exceed the limit, we drop the request.
"""

import time

class APIGateway:
    def __init__(self, max_requests, time_window):
        self.max_requests = max_requests
        self.time_window = time_window # in seconds
        self.client_logs = {}

    def handle_request(self, ip_address):
        current_time = time.time()
        
        # Initialize new IP
        if ip_address not in self.client_logs:
            self.client_logs[ip_address] = []

        # Filter out old requests outside the time window
        self.client_logs[ip_address] = [t for t in self.client_logs[ip_address] if current_time - t < self.time_window]

        if len(self.client_logs[ip_address]) < self.max_requests:
            self.client_logs[ip_address].append(current_time)
            print(f"  \033[32m[200 OK]\033[0m Request accepted from {ip_address}")
        else:
            print(f"  \033[31m[429 TOO MANY REQUESTS]\033[0m Rate limit exceeded for {ip_address}!")

if __name__ == "__main__":
    print("\033[1m\n--- API Rate Limiter ---\033[0m")
    gateway = APIGateway(max_requests=3, time_window=5)
    
    # Simulate a rapid-fire attack
    for _ in range(5):
        gateway.handle_request("192.168.1.50")
        time.sleep(0.5)