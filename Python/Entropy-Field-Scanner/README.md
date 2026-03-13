# ENTROPY-FIELD-SCANNER

A high-precision forensic tool designed to measure data density. By calculating the Shannon Entropy of digital assets, this scanner determines the randomness of a file—identifying whether data is plain text, compressed, or encrypted.

## 🧠 Core Logic
The engine utilizes the Shannon Entropy Formula:
H(X) = -Σ P(xi) log2 P(xi)

ANALYSIS SCALE:
- Low Entropy (< 4.0): Indicates high predictability (e.g., source code, plain text).
- Balanced Entropy (4.5 - 6.5): Indicates structured data (e.g., compiled binaries, rich media).
- High Entropy (> 7.5): Indicates maximum randomness (e.g., encrypted files, compressed archives).

## 🛠️ Technical Stack
- Language: Python 3.x
- Libraries: math, os, collections
- Features: Real-time byte distribution analysis and crash-resistant error handling.

## 🚀 Execution Guide
To run the scanner, follow these plain-text steps:
1. Ensure Python 3 is installed on your workstation.
2. Open your terminal or command prompt.
3. Navigate to the project directory.
4. Run the command: python entropy_scanner.py
5. When prompted, provide the full target path of the file you wish to analyze.
6. Type 'exit' to deactivate the scanner engine.

---
Lead Developer: Syed Saad Bin Irfan

Logic: Data Forensics & Information Theory
