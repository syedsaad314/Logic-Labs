/*
 * Problem (The Commons): Letting clients talk directly to 50 different microservices 
 * exposes your internal network, makes authentication a nightmare, and breaks immediately 
 * if an internal IP changes.
 * Logic: The API Gateway. A single, hardened entry point for all incoming traffic. 
 * It intercepts the request, verifies authorization in O(1) time, and routes the packet 
 * to the correct internal microservice address using a hash map.
 */

#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class APIGateway {
private:
    unordered_map<string, string> routingTable;
    unordered_map<string, bool> validTokens;

public:
    APIGateway() {
        // Internal Microservice IP mapping
        routingTable["/api/users"] = "10.0.1.15:8080 (User Service)";
        routingTable["/api/orders"] = "10.0.1.22:8081 (Order Service)";
        routingTable["/api/payments"] = "10.0.1.30:8082 (Payment Service)";
        
        // Mock authentication tokens
        validTokens["Bearer-77X9"] = true;
    }

    void handleRequest(const string& route, const string& token) {
        if (validTokens.find(token) == validTokens.end()) {
            cout << "  \033[31m[401 UNAUTHORIZED]\033[0m Invalid or missing Auth Token.\n";
            return;
        }

        if (routingTable.find(route) != routingTable.end()) {
            cout << "  \033[32m[200 OK]\033[0m Packet routed -> " << routingTable[route] << "\n";
        } else {
            cout << "  \033[33m[404 NOT FOUND]\033[0m Endpoint '" << route << "' does not exist.\n";
        }
    }
};

int main() {
    APIGateway gateway;
    string route, token;

    cout << "\033[1m\n--- EdgeNode Gateway (Reverse Proxy) ---\033[0m\n";
    cout << "\033[90mSimulating incoming external traffic. Valid token: 'Bearer-77X9'\033[0m\n";
    cout << "\033[90mCommands: 'req <route> <token>' or 'exit'\033[0m\n\n";

    while (true) {
        cout << "\033[1mExternal Request > \033[0m";
        string cmd;
        cin >> cmd;
        if (cmd == "exit") break;

        if (cmd == "req") {
            cin >> route >> token;
            gateway.handleRequest(route, token);
        } else {
            cout << "  \033[31mInvalid command.\033[0m\n";
        }
    }
    return 0;
}