/*
 * Topic: Memory Management & Pointers (LRU Cache)
 * Problem: Systems only have so much memory. When a cache hits its limit, we need 
 * to evict the Least Recently Used (LRU) item to make room for new data. 
 * Approach: We use a Hash Map (unordered_map) paired with a Doubly Linked List (std::list). 
 * The list tracks the order of usage, and the map gives us instant O(1) access to the nodes. 
 * When we touch a piece of data, we move it to the front of the list. When we run out of space, 
 * we pop the back of the list.
 */

#include <iostream>
#include <list>
#include <unordered_map>
#include <string>

using namespace std;

// Notion-inspired warm terminal palette
#define BOLD "\033[1m"
#define CYAN "\033[36m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

class LRUCache {
    int capacity;
    list<string> lruQueue;
    unordered_map<string, list<string>::iterator> cacheMap;

public:
    LRUCache(int cap) : capacity(cap) {}

    void refer(string key) {
        if (cacheMap.find(key) == cacheMap.end()) {
            cout << YELLOW << "  [Miss] Data not in cache. Fetching & Storing..." << RESET << "\n";
            if (lruQueue.size() == capacity) {
                string last = lruQueue.back();
                lruQueue.pop_back();
                cacheMap.erase(last);
                cout << "  [Evicted] Removed least recently used key: " << last << "\n";
            }
        } else {
            cout << GREEN << "  [Hit] Data found in cache! Moving to front." << RESET << "\n";
            lruQueue.erase(cacheMap[key]);
        }
        lruQueue.push_front(key);
        cacheMap[key] = lruQueue.begin();
    }

    void display() {
        cout << CYAN << "  Current Cache State (Most -> Least Recent): [ " << RESET;
        for (auto const& i : lruQueue) {
            cout << i << " ";
        }
        cout << CYAN << "]" << RESET << "\n";
    }
};

int main() {
    cout << BOLD << "\n--- Memory Architecture: LRU Cache ---" << RESET << "\n";
    int cap;
    cout << "Set maximum cache capacity (e.g., 3): ";
    cin >> cap;

    LRUCache cache(cap);
    string input;
    
    cout << "\nType a data key (e.g., 'A', 'B') to access it. Type 'exit' to stop.\n";
    while (true) {
        cout << BOLD << "> " << RESET;
        cin >> input;
        if (input == "exit") break;
        
        cache.refer(input);
        cache.display();
    }
    return 0;
}