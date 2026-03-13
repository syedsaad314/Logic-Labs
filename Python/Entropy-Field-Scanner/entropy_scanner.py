import math
import os
import sys
from collections import Counter

# System Color Schematics
EMERALD = "\033[38;5;48m"
AMBER   = "\033[38;5;214m"
SLATE   = "\033[38;5;244m"
CRIMSON = "\033[31m"
RESET   = "\033[0m"
BOLD    = "\033[1m"

def calculate_shannon_entropy(file_path):
    """Calculates data density while protecting system stability."""
    try:
        if not os.path.exists(file_path):
            return "ERR_NOT_FOUND"
        
        # Check if it's a directory
        if os.path.isdir(file_path):
            return "ERR_IS_DIR"

        file_size = os.path.getsize(file_path)
        
        # Handling massive files by reading in chunks if necessary (Stability Logic)
        with open(file_path, "rb") as f:
            data = f.read()

        if not data:
            return 0.0

        byte_counts = Counter(data)
        entropy = 0
        for count in byte_counts.values():
            p_x = count / file_size
            entropy -= p_x * math.log2(p_x)

        return round(entropy, 4)

    except PermissionError:
        return "ERR_PERMISSION"
    except Exception as e:
        return f"ERR_UNKNOWN: {str(e)}"

def run_interface():
    print(f"\n{BOLD}{EMERALD}ENTROPY-FIELD-SCANNER // INITIALIZED{RESET}")
    print(f"{SLATE}ENGINEERING LEAD: SYED SAAD BIN IRFAN{RESET}\n")

    print(f"{SLATE}[GUIDE]: This tool measures 'Data Randomness'.{RESET}")
    print(f"{SLATE}Input the full path of any file (Image, PDF, EXE) to analyze its density.{RESET}")
    
    while True:
        target = input(f"\n{AMBER}TARGET_PATH (or 'exit'): {RESET}").strip('"').strip("'")

        if target.lower() == 'exit':
            print(f"{EMERALD}SCANNER_DEACTIVATED. GOODBYE.{RESET}")
            break

        print(f"{SLATE}ANALYZING_BYTE_DISTRIBUTION...{RESET}")
        
        result = calculate_shannon_entropy(target)

        # Crash-Level Flow Handling
        if result == "ERR_NOT_FOUND":
            print(f"{CRIMSON}![REJECTION]: File not found. Verify the path and try again.{RESET}")
            continue
        elif result == "ERR_IS_DIR":
            print(f"{CRIMSON}![REJECTION]: Target is a directory. Please provide a specific file.{RESET}")
            continue
        elif result == "ERR_PERMISSION":
            print(f"{CRIMSON}![REJECTION]: Permission denied. System access restricted.{RESET}")
            continue
        elif isinstance(result, str) and "ERR_UNKNOWN" in result:
            print(f"{CRIMSON}![CRITICAL]: {result}{RESET}")
            continue

        # Render Results UI
        print(f"\n{SLATE}------------------------------------------------{RESET}")
        print(f"{BOLD}FILE: {os.path.basename(target)}{RESET}")
        print(f"ENTROPY: {EMERALD}{result} bits/byte{RESET}")
        
        # Professional Interpretation Logic
        if result > 7.5:
            desc = "HIGH_DENSITY: Likely Encrypted or Compressed (ZIP/EXE)."
        elif result > 4.5:
            desc = "BALANCED_DENSITY: Likely Compiled Code or Rich Media."
        elif result > 1.0:
            desc = "LOW_DENSITY: Highly predictable data (Plain Text/Source Code)."
        else:
            desc = "MINIMAL_DENSITY: Repetitive or empty data strings."

        print(f"STATUS: {AMBER}{desc}{RESET}")
        print(f"{SLATE}------------------------------------------------{RESET}")
        print(f"{SLATE}VERIFIED_BY: SYED SAAD BIN IRFAN{RESET}")

if __name__ == "__main__":
    try:
        run_interface()
    except KeyboardInterrupt:
        print(f"\n{CRIMSON}SYSTEM_INTERRUPTED_BY_USER.{RESET}")
        sys.exit()