"""
Problem: In-memory data is lost the moment the script stops. 
Logic: Persistence Wrapper. We create a simple class that automatically 
saves its state to a JSON file every time the data is updated, 
creating a lightweight "Database" for our dashboard metrics.
"""

import json

class MetricStore:
    def __init__(self, filename="metrics.json"):
        self.filename = filename
        self.data = {"peak_load": 0, "total_requests": 0}

    def update(self, key, value):
        self.data[key] = value
        with open(self.filename, 'w') as f:
            json.dump(self.data, f)
        print(f"  \033[32m[Saved]\033[0m Persisted {key} to disk.")

if __name__ == "__main__":
    print("\033[1m\n--- Metric Persistence Layer ---\033[0m")
    store = MetricStore()
    store.update("peak_load", 88)