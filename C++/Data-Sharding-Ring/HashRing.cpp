/*
 * Problem: When you have 10 database servers, how do you know which server holds a specific 
 * user's data? If you just use (UserID % 10), adding an 11th server breaks everything.
 * Logic: Consistent Hashing. We map servers to a "Hash Ring" using a hash function. 
 * When a user's data needs to be stored, we hash their ID and place it in the *next* * available server on the ring. This is how massive databases scale horizontally.
 */

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

#define BOLD "\033[1m"
#define GRAY "\033[90m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

class ConsistentHashRing {
private:
    map<int, string> ring; // Maps Hash -> Server IP

    // Simple string hashing function for demonstration
    int hashFunction(const string& key) {
        int hash = 0;
        for (char c : key) hash = (hash * 31 + c) % 360; // 360 degree ring
        return hash;
    }

public:
    void addServer(const string& ip) {
        int hash = hashFunction(ip);
        ring[hash] = ip;
        cout << "  " << GREEN << "[+] Server Added:" << RESET << " " << ip << " at position " << hash << "°\n";
    }

    void removeServer(const string& ip) {
        int hash = hashFunction(ip);
        ring.erase(hash);
        cout << "  \033[31m[-] Server Removed:\033[0m " << ip << "\n";
    }

    string getServer(const string& dataKey) {
        if (ring.empty()) return "NO_SERVERS";
        
        int dataHash = hashFunction(dataKey);
        
        // Find the first server hash that is >= dataHash
        auto it = ring.lower_bound(dataHash);
        
        // If we went past the end, wrap around to the first server
        if (it == ring.end()) {
            it = ring.begin();
        }
        
        return it->second;
    }
};

int main() {
    cout << BOLD << "\n--- Distributed Database Hash Ring ---" << RESET << "\n";
    
    ConsistentHashRing cluster;
    cluster.addServer("Node-A (10.0.0.1)");
    cluster.addServer("Node-B (10.0.0.2)");
    cluster.addServer("Node-C (10.0.0.3)");
    
    cout << GRAY << "\nType a user ID or piece of data to see where it gets routed." << RESET << "\n";
    cout << GRAY << "Type 'add <NodeName>', 'drop <NodeName>', or 'exit'." << RESET << "\n\n";

    string input;
    while (true) {
        cout << BOLD << "Cluster > " << RESET;
        getline(cin, input);
        if (input == "exit") break;

        if (input.substr(0, 4) == "add ") {
            cluster.addServer(input.substr(4));
        } else if (input.substr(0, 5) == "drop ") {
            cluster.removeServer(input.substr(5));
        } else {
            string routedServer = cluster.getServer(input);
            cout << "  " << CYAN << "Routing data '" << input << "' -> " << RESET << BOLD << routedServer << RESET << "\n";
        }
    }
    return 0;
}