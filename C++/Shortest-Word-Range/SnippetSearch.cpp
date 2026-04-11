/*
 * Problem: When a user searches for multiple keywords, we need to find the smallest 
 * continuous block of text that contains all of them.
 * Logic: Sliding Window Algorithm. We expand our "window" to the right until we have 
 * all the keywords, then shrink it from the left to find the tightest possible fit in O(N) time.
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

// Minimalist Terminal Styling
#define BOLD "\033[1m"
#define GRAY "\033[90m"
#define RESET "\033[0m"

void findShortestSnippet() {
    cout << BOLD << "\n--- Document Search Engine ---" << RESET << "\n";
    
    string docInput;
    cout << GRAY << "Enter the full document text: " << RESET;
    getline(cin, docInput);
    
    string targetInput;
    cout << GRAY << "Enter the target words to find (space-separated): " << RESET;
    getline(cin, targetInput);

    vector<string> document;
    stringstream ss(docInput);
    string word;
    while (ss >> word) document.push_back(word);

    unordered_map<string, int> targetCounts;
    stringstream ssTargets(targetInput);
    int requiredWords = 0;
    while (ssTargets >> word) {
        targetCounts[word]++;
        requiredWords++;
    }

    int left = 0, right = 0, matchCount = 0;
    int minLen = document.size() + 1, minStart = 0;
    unordered_map<string, int> windowCounts;

    while (right < document.size()) {
        string rightWord = document[right];
        if (targetCounts.count(rightWord)) {
            windowCounts[rightWord]++;
            if (windowCounts[rightWord] <= targetCounts[rightWord]) {
                matchCount++;
            }
        }

        while (matchCount == requiredWords) {
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                minStart = left;
            }

            string leftWord = document[left];
            if (targetCounts.count(leftWord)) {
                windowCounts[leftWord]--;
                if (windowCounts[leftWord] < targetCounts[leftWord]) {
                    matchCount--;
                }
            }
            left++;
        }
        right++;
    }

    if (minLen <= document.size()) {
        cout << "\n" << BOLD << "Shortest Snippet Found:" << RESET << " [ ";
        for (int i = minStart; i < minStart + minLen; i++) {
            cout << document[i] << " ";
        }
        cout << "]\n";
    } else {
        cout << "\n  \033[31mCould not find all target words in the document.\033[0m\n";
    }
}

int main() {
    findShortestSnippet();
    return 0;
}