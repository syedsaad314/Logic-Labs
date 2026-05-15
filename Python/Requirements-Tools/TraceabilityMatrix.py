"""
* [PROBLEM STATEMENT]
* In complex software engineering projects, mapping Business Requirements 
* to Test Cases manually is tedious and results in missing coverage. 
* We need a script that scans documentation and automatically maps 
* requirement IDs to their corresponding tests.
*
* [LOGIC & INSIGHT]
* I built an automated Traceability Matrix parser using Python and Regex. 
* It scans raw text for standard requirement tags (e.g., [REQ-01]) and 
* maps them to test tags (e.g., [TEST-01]). I specifically engineered 
* the output to highlight "Orphaned Requirements" (reqs with no tests) 
* so quality assurance teams can immediately spot gaps in testing before 
* moving to production.
"""

import re

class TraceabilityEngine:
    def __init__(self, raw_doc):
        self.raw_doc = raw_doc
        self.matrix = {}

    def parse_and_map(self):
        # Extract blocks like: [REQ-01] User Login -> Tests: [TEST-01], [TEST-02]
        pattern = r"\[(REQ-\d+)\][^\n]+Tests:\s*([^#\n]+)"
        matches = re.findall(pattern, self.raw_doc, re.IGNORECASE)

        for req_id, test_string in matches:
            # Find all test IDs in the test string
            tests = re.findall(r"\[(TEST-\d+)\]", test_string)
            self.matrix[req_id] = tests

    def generate_report(self):
        print("\033[1m--- REQUIREMENT TRACEABILITY MATRIX ---\033[0m")
        for req, tests in self.matrix.items():
            if not tests:
                print(f"  \033[31m[WARNING]\033[0m {req} is ORPHANED (No tests found!)")
            else:
                test_list = ", ".join(tests)
                print(f"  \033[32m[COVERED]\033[0m {req} mapped to -> {test_list}")

# Mock Documentation String
docs = """
Section 1.1: Authentication
[REQ-01] The system must encrypt passwords. Tests: [TEST-01], [TEST-02]
[REQ-02] The system must lock out users after 3 failed attempts. Tests: [TEST-03]

Section 1.2: UI Rendering
[REQ-03] Dashboard must load within 2 seconds. Tests: None defined yet
"""

engine = TraceabilityEngine(docs)
engine.parse_and_map()
engine.generate_report()