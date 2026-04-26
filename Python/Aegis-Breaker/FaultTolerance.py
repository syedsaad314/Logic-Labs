"""
Problem (The Commons): If the Database goes down, your web servers will keep sending queries, 
timing out, hanging threads, and eventually crashing the entire cluster (Cascading Failure).
Logic: The Circuit Breaker. If a downstream service fails 'X' times in a row, the circuit "Trips" 
(Opens). All subsequent requests are instantly rejected to give the database time to recover, 
saving server threads. After a timeout, it allows one request through to test if it's fixed.
"""

import time

class CircuitBreaker:
    def __init__(self, failure_threshold=3, recovery_timeout=5):
        self.failure_threshold = failure_threshold
        self.recovery_timeout = recovery_timeout
        self.failures = 0
        self.state = "CLOSED" # CLOSED = Normal, OPEN = Tripped
        self.last_failure_time = None

    def execute_request(self, success_simulation):
        if self.state == "OPEN":
            if time.time() - self.last_failure_time > self.recovery_timeout:
                print("  \033[33m[Circuit HALF-OPEN]\033[0m Testing connection...")
                self.state = "HALF-OPEN"
            else:
                print("  \033[31m[Circuit OPEN]\033[0m Request blocked. Service is resting.")
                return

        if success_simulation:
            print("  \033[32m[200 OK]\033[0m Request succeeded.")
            self.failures = 0
            self.state = "CLOSED"
        else:
            self.failures += 1
            print(f"  \033[33m[500 ERROR]\033[0m Request failed. Failure count: {self.failures}/{self.failure_threshold}")
            if self.failures >= self.failure_threshold:
                print("  \033[31m[!] CRITICAL: CIRCUIT TRIPPED (OPEN).\033[0m Halting traffic.")
                self.state = "OPEN"
                self.last_failure_time = time.time()

if __name__ == "__main__":
    cb = CircuitBreaker()
    print("\033[1m\n--- Aegis Breaker (Fault Tolerance Engine) ---\033[0m")
    print("\033[90mSimulate API calls. Type 's' for success, 'f' for failure, 'exit' to quit.\033[0m\n")

    while True:
        cmd = input("\033[1mSimulate Call (s/f) > \033[0m").strip().lower()
        if cmd == 'exit': break
        
        if cmd == 's':
            cb.execute_request(True)
        elif cmd == 'f':
            cb.execute_request(False)
        else:
            print("  \033[31mInvalid input.\033[0m")