"""
* [PROBLEM STATEMENT]
* Manually checking server logs or news feeds for new security CVEs (Common 
* Vulnerabilities and Exposures) is impossible. I need a tool that can parse 
* structured or semi-structured data strings and flag critical keywords like 
* 'SQL Injection', 'RCE', or 'Exploit'.
*
* [LOGIC & INSIGHT]
* I used Python's 'Regular Expressions' (Regex) to build a pattern-matching engine. 
* I personally designed the 'Risk Score' logic: the script doesn't just find a word; 
* it calculates a score based on frequency and severity. It converts raw log 
* text into a professional JSON-style report. This shows my ability to handle 
* real-world unstructured data and turn it into actionable intelligence.
"""

import re
import json

class ThreatEngine:
    def __init__(self):
        self.keywords = {
            "CRITICAL": r"(RCE|Exploit|Zero-Day|Overflow)",
            "HIGH": r"(SQL Injection|XSS|Auth Bypass)",
            "MEDIUM": r"(Info Leak|Deprecated|Header Missing)"
        }
    
    def analyze_feed(self, raw_text):
        report = {"timestamp": "2026-05-09", "alerts": [], "total_risk_score": 0}
        
        for severity, pattern in self.keywords.items():
            matches = re.findall(pattern, raw_text, re.IGNORECASE)
            if matches:
                weight = 10 if severity == "CRITICAL" else (5 if severity == "HIGH" else 2)
                report["alerts"].append({
                    "severity": severity,
                    "findings": list(set(matches)),
                    "count": len(matches)
                })
                report["total_risk_score"] += (len(matches) * weight)
        
        return report

# Mock Data
feed_data = "Urgent: New Zero-Day Exploit found in Linux Kernel. Also, check for SQL Injection in login forms."
engine = ThreatEngine()
result = engine.analyze_feed(feed_data)

print("\033[1m--- THREAT ANALYSIS REPORT ---\033[0m")
print(json.dumps(result, indent=4))