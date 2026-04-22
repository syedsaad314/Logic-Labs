"""
Problem: In a network of servers (or city intersections), how do we find the absolute 
fastest route from Point A to Point B when different paths have different latencies/costs?
Logic: Dijkstra's Algorithm using a Priority Queue. It mathematically explores the cheapest 
nodes first, guaranteeing the most efficient path is found without checking every single 
unnecessary route.
"""

import heapq

class NetworkGraph:
    def __init__(self):
        # Dictionary of node -> {neighbor: latency_cost}
        self.nodes = {
            'RouterA': {'RouterB': 5, 'RouterC': 2},
            'RouterB': {'RouterD': 4, 'RouterE': 2},
            'RouterC': {'RouterB': 8, 'RouterE': 7},
            'RouterD': {'RouterE': 6, 'RouterF': 3},
            'RouterE': {'RouterF': 1},
            'RouterF': {}
        }

    def find_fastest_route(self, start, end):
        if start not in self.nodes or end not in self.nodes:
            return None, "Invalid nodes specified."

        # Priority queue stores (current_cost, current_node)
        queue = [(0, start)]
        distances = {node: float('inf') for node in self.nodes}
        distances[start] = 0
        previous_nodes = {node: None for node in self.nodes}

        while queue:
            current_distance, current_node = heapq.heappop(queue)

            # If we reached the destination, stop searching
            if current_node == end:
                break

            for neighbor, weight in self.nodes[current_node].items():
                distance = current_distance + weight

                # Only update if we found a strictly shorter path
                if distance < distances[neighbor]:
                    distances[neighbor] = distance
                    previous_nodes[neighbor] = current_node
                    heapq.heappush(queue, (distance, neighbor))

        # Reconstruct path
        path = []
        current = end
        while current is not None:
            path.append(current)
            current = previous_nodes[current]
        path.reverse()

        return path, distances[end]

if __name__ == "__main__":
    print("\033[1m\n--- NodePath Router (Dijkstra Optimization) ---\033[0m")
    net = NetworkGraph()
    
    print("\033[90mAvailable Nodes:\033[0m", ", ".join(net.nodes.keys()))
    print("\033[90mThe network is mapped. Let's route some packets.\033[0m\n")

    while True:
        try:
            start_node = input("\033[1mEnter Source Node (or 'exit') > \033[0m").strip()
            if start_node.lower() == 'exit': break
            
            end_node = input("\033[1mEnter Destination Node > \033[0m").strip()
            
            print(f"\n  \033[36m[Calculating]\033[0m Routing {start_node} -> {end_node}...")
            
            path, total_cost = net.find_fastest_route(start_node, end_node)
            
            if total_cost == float('inf'):
                print("  \033[31m[-] No valid route exists.\033[0m\n")
            elif not path:
                print("  \033[31m[-] Routing failed: Invalid inputs.\033[0m\n")
            else:
                print(f"  \033[32m[✓] Optimal Route Found!\033[0m")
                print(f"  \033[1mPath:\033[0m {' ➔ '.join(path)}")
                print(f"  \033[1mTotal Latency:\033[0m {total_cost}ms\n")
                
        except KeyboardInterrupt:
            break