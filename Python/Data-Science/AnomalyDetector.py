"""
* [PROBLEM STATEMENT]
* In cybersecurity, an "Attack" is usually just an unusual pattern in data. 
* We need a mathematical way to look at a list of login attempts and 
* automatically flag the ones that are far outside the normal average 
* (Outliers).
*
* [LOGIC & INSIGHT]
* I implemented a 'Standard Deviation' (Z-Score) algorithm. I calculated 
* the Mean and Deviation of the login durations. If an attempt takes 
* significantly longer (or shorter) than the average, it is flagged 
* as "Suspicious." This demonstrates my ability to use pure math and 
* Python to solve real-world security automation problems.
"""

import math

class AnomalyDetector:
    def __init__(self, data_points):
        self.data = data_points
        self.mean = sum(data_points) / len(data_points)
        self.std_dev = self.calculate_std_dev()

    def calculate_std_dev(self):
        variance = sum((x - self.mean) ** 2 for x in self.data) / len(self.data)
        return math.sqrt(variance)

    def find_anomalies(self, threshold=2):
        print(f"\033[1mAnalyzing {len(self.data)} events. Mean: {self.mean:.2f}ms\033[0m")
        anomalies = []
        for x in self.data:
            z_score = (x - self.mean) / self.std_dev
            if abs(z_score) > threshold:
                anomalies.append(x)
                print(f"  \033[31m[ANOMALY]\033[0m Value {x} detected (Z-Score: {z_score:.2f})")
        return anomalies

# Mock login response times (in ms)
login_times = [102, 110, 98, 105, 115, 800, 101, 95, 5] # 800 is slow, 5 is bot-fast
detector = AnomalyDetector(login_times)
detector.find_anomalies()