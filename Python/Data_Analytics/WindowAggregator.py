"""
Problem: Writing individual click-events to a database 10,000 times a second creates massive I/O 
bottlenecks and destroys database indexes.
Logic: Tumbling Time Windows. We collect raw events in memory over a fixed time span (e.g., 5 seconds). 
Once the window closes, we aggregate the data (summing the clicks) and perform a single, 
highly efficient bulk-write to the database.
"""

import time
import threading

class WindowAggregator:
    def __init__(self, window_size_sec=5):
        self.window_size = window_size_sec
        self.event_buffer = []
        self.lock = threading.Lock()
        self.running = True
        
        # Start background aggregation thread
        threading.Thread(target=self._process_window, daemon=True).start()

    def log_event(self, user_id, action):
        with self.lock:
            self.event_buffer.append({"user": user_id, "action": action})
            print(f"  \033[90m[Ingest]\033[0m Buffered event from {user_id}")

    def _process_window(self):
        while self.running:
            time.sleep(self.window_size)
            with self.lock:
                if not self.event_buffer:
                    continue
                
                # Aggregate logic
                total_events = len(self.event_buffer)
                print(f"\n  \033[36m[Window Closed]\033[0m Processing {self.window_size}s batch...")
                print(f"  \033[32m[DB Bulk Write]\033[0m Flushed {total_events} aggregated events to storage.\n")
                
                # Clear buffer for the next window
                self.event_buffer.clear()
                print("\033[1mEvent Stream > \033[0m", end="", flush=True)

if __name__ == "__main__":
    print("\033[1m\n--- Tumbling Window Aggregator ---\033[0m")
    print("\033[90mBackground thread flushes data every 5 seconds.\033[0m")
    
    aggregator = WindowAggregator(window_size_sec=5)
    
    try:
        while True:
            cmd = input("\033[1mEvent Stream (press Enter to log, 'exit' to quit) > \033[0m")
            if cmd == 'exit':
                aggregator.running = False
                break
            aggregator.log_event("User_" + str(int(time.time()) % 1000), "CLICK")
    except KeyboardInterrupt:
        pass