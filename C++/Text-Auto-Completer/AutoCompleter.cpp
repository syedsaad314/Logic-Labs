/*
 * Problem: When a user types in a search bar, we need to instantly suggest words that 
 * start with those letters. Searching a raw list of millions of words is too slow.
 * Logic: We build a "Trie" (Prefix Tree). Each node represents a letter. This allows 
 * us to find all words starting with a prefix in O(L) time, where L is the prefix length.
 */

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

#define BOLD "\033[1m"
#define GRAY "\033[90m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord = false;
};

class Trie {
private:
    TrieNode* root;

    void dfs(TrieNode* node, string prefix, vector<string>& results) {
        if (node->isEndOfWord) results.push_back(prefix);
        for (auto pair : node->children) {
            dfs(pair.second, prefix + pair.first, results);
        }
    }

public:
    Trie() { root = new TrieNode(); }

    void insert(string word) {
        TrieNode* current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->isEndOfWord = true;
    }

    vector<string> getSuggestions(string prefix) {
        TrieNode* current = root;
        vector<string> results;
        for (char ch : prefix) {
            if (current->children.find(ch) == current->children.end()) {
                return results; // Prefix not found
            }
            current = current->children[ch];
        }
        dfs(current, prefix, results);
        return results;
    }
};

int main() {
    Trie autocomplete;
    cout << BOLD << "\n--- Text Auto-Completer Engine ---" << RESET << "\n";
    cout << GRAY << "Initializing dictionary database...\033[0m\n";
    
    // Seed data
    vector<string> dictionary = {"software", "solution", "system", "syntax", "synchronize", "server", "security", "saad", "student"};
    for (string w : dictionary) autocomplete.insert(w);
    cout << GREEN << "  ✓ Dictionary loaded." << RESET << "\n\n";

    cout << GRAY << "Type a prefix (e.g., 'sy', 'sa', 'so') or type 'exit' to quit.\033[0m\n";

    string input;
    while (true) {
        cout << BOLD << "> " << RESET;
        cin >> input;
        if (input == "exit") break;

        vector<string> suggestions = autocomplete.getSuggestions(input);
        
        if (suggestions.empty()) {
            cout << "  \033[31mNo suggestions found.\033[0m\n";
        } else {
            cout << CYAN << "  Suggestions: " << RESET;
            for (string s : suggestions) cout << s << "   ";
            cout << "\n";
        }
    }
    return 0;
}