#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

void analyzeFrequency(const string& text) {
    unordered_map<char, int> freq;
    for (char c : text) if (isalpha(c)) freq[tolower(c)]++;
    
    cout << "Character Frequencies:\n";
    for (const auto& pair : freq) {
        cout << pair.first << ": " << pair.second << "\n";
    }
}

int main() {
    string input;
    cout << "Enter dataset string: ";
    getline(cin, input);
    analyzeFrequency(input);
    return 0;
}