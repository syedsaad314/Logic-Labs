"""
Problem: You have millions of system logs. You need to know instantly if CPU spikes 
are "normal high traffic" or a "cyber attack," but hardcoding limits (e.g., > 90%) creates false alarms.
Logic: Z-Score Algorithm. We calculate the rolling mean and standard deviation. 
If a new data point deviates too far from the statistical norm (Z-Score > 2.0), we flag it as an anomaly.
"""

import math

class AnomalyDetector:
    def __init__(self):
        self.data_window = []

    def log_metric(self, value):
        self.data_window.append(value)
        if len(self.data_window) < 3:
            return  # Need more data for stats

        # Calculate Mean
        mean = sum(self.data_window) / len(self.data_window)
        
        # Calculate Standard Deviation
        variance = sum((x - mean) ** 2 for x in self.data_window) / len(self.data_window)
        std_dev = math.sqrt(variance)

        if std_dev == 0: return

        # Calculate Z-Score for the latest value
        z_score = abs(value - mean) / std_dev

        if z_score > 2.0:
            print(f"  \033[31m[ANOMALY DETECTED]\033[0m Value: {value} | Z-Score: {z_score:.2f} (Statistically improbable)")
        else:
            print(f"  \033[32m[Metric Normal]\033[0m Value: {value} | Z-Score: {z_score:.2f}")

if __name__ == "__main__":
    print("\033[1m\n--- Z-Score Statistical Anomaly Detector ---\033[0m")
    detector = AnomalyDetector()
    
    traffic_data = [120, 125, 119, 122, 130, 121, 500, 125] # 500 is the anomaly
    for point in traffic_data:
        detector.log_metric(point)