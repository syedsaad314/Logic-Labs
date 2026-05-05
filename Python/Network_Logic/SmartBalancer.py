"""
Problem: Standard Load Balancers send traffic "Round Robin" (1, 2, 3, 1, 2, 3). 
But if Server 2 is lagging, Round Robin will keep hammering it, making the lag worse.
Logic: Least Latency Routing. We track the response time of each server and 
always route the next request to the fastest available node.
"""

import time
import random

class LoadBalancer:
    def __init__(self):
        # Initial health/latency stats for 3 nodes
        self.nodes = {"Node_A": 10, "Node_B": 50, "Node_C": 15}

    def route_request(self):
        # Find the node with the minimum latency
        best_node = min(self.nodes, key=self.nodes.get)
        print(f"  \033[32m[Routing]\033[0m Best path: {best_node} (Latency: {self.nodes[best_node]}ms)")
        
        # Simulate latency change after processing
        self.nodes[best_node] += random.randint(-5, 20)

if __name__ == "__main__":
    print("\033[1m\n--- Latency-Aware Load Balancer ---\033[0m")
    lb = LoadBalancer()
    for _ in range(5):
        lb.route_request()
        time.sleep(0.5)