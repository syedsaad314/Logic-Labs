"""
Problem: Loading a 10GB server log file into Python using `file.readlines()` 
will consume 10GB of RAM instantly, crashing the container.
Logic: Generators (the `yield` keyword). We read the file one line at a time, 
process it, and discard it. It processes 10GB of data while only ever using 
a few kilobytes of RAM.
"""

import sys

def process_logs_lazily(simulated_log_data):
    """A generator function that yields one line at a time."""
    for line in simulated_log_data:
        # Simulate heavy parsing
        if "ERROR" in line:
            yield f"  \033[31m[CRITICAL]\033[0m {line.strip()}"
        elif "WARN" in line:
            yield f"  \033[33m[WARNING]\033[0m {line.strip()}"

if __name__ == "__main__":
    print("\033[1m\n--- Memory-Efficient Log Streamer ---\033[0m")
    
    # Simulating an infinitely large file
    massive_log_file = [
        "INFO: System boot",
        "WARN: CPU temp 85C",
        "INFO: User login",
        "ERROR: Database timeout"
    ]

    # Process logs without loading them all into memory
    log_generator = process_logs_lazily(massive_log_file)
    
    for alert in log_generator:
        print(alert)