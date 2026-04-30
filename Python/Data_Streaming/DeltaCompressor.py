"""
Problem: Sending full sensor data packets (e.g., GPS coordinates) every 10ms consumes 
massive bandwidth when 99% of the data hasn't changed since the last packet.
Logic: Delta Encoding. We only transmit the *difference* between the current value 
and the previous one. If the temperature was 30.5 and is now 30.6, we just send "0.1", 
drastically reducing payload size.
"""

class DeltaStreamer:
    def __init__(self):
        self.last_value = 0

    def compress(self, current_value):
        delta = current_value - self.last_value
        self.last_value = current_value
        return delta

if __name__ == "__main__":
    print("\033[1m\n--- Delta-Encoded Streamer ---\033[0m")
    stream = DeltaStreamer()
    raw_data = [100.0, 100.5, 101.2, 101.1, 105.0]
    
    print(f"Raw Data: {raw_data}")
    compressed = [stream.compress(v) for v in raw_data]
    print(f"Compressed Deltas: \033[36m{compressed}\033[0m")