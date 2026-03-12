import time
import random
import os

class NeuralSync:
    def __init__(self, node_count):
        self.nodes = {f"NODE_{i:03}": [] for i in range(node_count)}
        self.sync_log = []

    def establish_synapse(self):
        n1, n2 = random.sample(list(self.nodes.keys()), 2)
        if n2 not in self.nodes[n1]:
            self.nodes[n1].append(n2)
            timestamp = time.strftime("%H:%M:%S")
            entry = f"[{timestamp}] SYNAPSE_CREATED: {n1} <-> {n2}"
            self.sync_log.append(entry)
            print(entry)

    def generate_report(self):
        """Generates a professional HTML report of the synchronization."""
        log_html = "".join([f'<div class="log-entry">> {entry}</div>' for entry in self.sync_log])
        
        html_content = f"""
        <!DOCTYPE html>
        <html>
        <head>
            <style>
                body {{ background: #02040a; color: #00bcd4; font-family: 'Consolas', monospace; padding: 40px; }}
                .terminal {{ border: 1px solid #1b222d; padding: 20px; background: #0a0d14; box-shadow: 0 0 20px rgba(0,188,212,0.1); }}
                .log-entry {{ font-size: 0.85rem; margin-bottom: 8px; border-left: 2px solid #00bcd4; padding-left: 15px; opacity: 0.9; }}
                .header {{ border-bottom: 1px solid #1b222d; margin-bottom: 20px; padding-bottom: 10px; display: flex; justify-content: space-between; }}
                .sig {{ color: #484f58; font-size: 0.7rem; letter-spacing: 2px; }}
            </style>
        </head>
        <body>
            <div class="terminal">
                <div class="header">
                    <span>NEURAL-SYNC-MAPPER // LIVE_REPORT</span>
                    <span class="sig">OPERATOR: SSBI-001</span>
                </div>
                {log_html}
            </div>
        </body>
        </html>
        """
        with open("live_feed.html", "w") as f:
            f.write(html_content)
        print(f"\n[!] REPORT_GENERATED: {os.path.abspath('live_feed.html')}")

    def run_mapping(self, cycles=15):
        print("--- INITIALIZING NEURAL SYNC MAPPER (SSBI-001) ---")
        for _ in range(cycles):
            self.establish_synapse()
            time.sleep(0.1)
        self.generate_report()
        print("--- MAPPING COMPLETE: SECTORS SYNCHRONIZED ---")

if __name__ == "__main__":
    mapper = NeuralSync(50)
    mapper.run_mapping()