"""
Problem: A standard in-memory rate limiter only works on a single server instance. If you 
have 3 backend nodes behind a load balancer, a user can bypass the limit by hitting different servers.
Logic: Centralized State. We move the token counts to a distributed Redis cache. Every backend 
node reads and writes to the exact same Redis key, ensuring the rate limit is globally 
enforced across the entire architecture.
"""

import time

class MockRedisCache:
    # Simulating a centralized Redis instance
    def __init__(self):
        self.store = {}

    def get(self, key):
        return self.store.get(key)

    def set(self, key, value):
        self.store[key] = value

redis_cluster = MockRedisCache()

class DistributedRateLimiter:
    def __init__(self, limit, window_seconds):
        self.limit = limit
        self.window = window_seconds

    def allow_request(self, user_ip):
        current_time = int(time.time())
        window_key = f"rate_limit:{user_ip}:{current_time // self.window}"

        # Fetch current request count from "Redis"
        requests = redis_cluster.get(window_key) or 0

        if requests >= self.limit:
            print(f"  \033[31m[429 Too Many Requests]\033[0m IP {user_ip} blocked across all nodes.")
            return False
        
        # Increment and save back to "Redis"
        redis_cluster.set(window_key, requests + 1)
        print(f"  \033[32m[200 OK]\033[0m IP {user_ip} allowed. (Request {requests + 1}/{self.limit})")
        return True

if __name__ == "__main__":
    print("\033[1m\n--- Distributed Redis Rate Limiter ---\033[0m")
    limiter = DistributedRateLimiter(limit=3, window_seconds=10)
    
    print("\033[90mSimulating global cluster limit: 3 requests per 10 seconds.\033[0m")
    
    while True:
        cmd = input("\n\033[1mSimulate request from IP (or 'exit') > \033[0m").strip()
        if cmd.lower() == 'exit': break
        limiter.allow_request(cmd)