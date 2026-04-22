/*
 * Problem: Fetching data from a main database is slow. We need a local cache, but memory 
 * is limited. When the cache is full, what do we delete to make room?
 * Logic: Least Recently Used (LRU) Cache. By combining a Hash Map (for instant lookups) 
 * with a Doubly Linked List (to track usage order), we achieve O(1) efficiency for both 
 * reading and writing. The oldest, unused data is automatically evicted.
 */

#include <iostream>
#include <unordered_map>
#include <list>
#include <string>

using namespace std;

class AeroCache {
private:
    int capacity;
    list<string> usageTracker; // Front = most recent, Back = least recent
    unordered_map<string, pair<string, list<string>::iterator>> cache;

public:
    AeroCache(int cap) : capacity(cap) {}

    void put(const string& key, const string& value) {
        if (cache.find(key) != cache.end()) {
            usageTracker.erase(cache[key].second);
        } else if (cache.size() >= capacity) {
            string lruKey = usageTracker.back();
            usageTracker.pop_back();
            cache.erase(lruKey);
            cout << "  \033[33m[Eviction]\033[0m Memory limit reached. Evicted key: '" << lruKey << "'\n";
        }
        
        usageTracker.push_front(key);
        cache[key] = {value, usageTracker.begin()};
        cout << "  \033[32m[Written]\033[0m " << key << " -> " << value << "\n";
    }

    void get(const string& key) {
        if (cache.find(key) == cache.end()) {
            cout << "  \033[31m[Cache Miss]\033[0m Key '" << key << "' not found.\n";
            return;
        }
        // Move to front (mark as most recently used)
        usageTracker.erase(cache[key].second);
        usageTracker.push_front(key);
        cache[key].second = usageTracker.begin();
        
        cout << "  \033[36m[Cache Hit]\033[0m " << key << " = " << cache[key].first << "\n";
    }

    void display() {
        cout << "  \033[90mCurrent Cache State (Most to Least Recent):\033[0m ";
        for (const string& k : usageTracker) cout << "[" << k << "] ";
        cout << "\n";
    }
};

int main() {
    cout << "\033[1m\n--- AeroCache Engine (LRU Memory) ---\033[0m\n";
    cout << "\033[90mCapacity is set to 3 slots. Watch how older data is dropped when full.\033[0m\n";
    cout << "\033[90mCommands: 'put <key> <val>', 'get <key>', 'exit'\033[0m\n\n";

    AeroCache memory(3);
    string cmd, key, val;

    while (true) {
        cout << "\033[1mAero> \033[0m";
        cin >> cmd;
        if (cmd == "exit") break;

        if (cmd == "put") {
            cin >> key >> val;
            memory.put(key, val);
        } else if (cmd == "get") {
            cin >> key;
            memory.get(key);
        } else {
            cout << "  \033[31mUnknown command. Use 'put' or 'get'.\033[0m\n";
        }
        memory.display();
        cout << "\n";
    }
    return 0;
}