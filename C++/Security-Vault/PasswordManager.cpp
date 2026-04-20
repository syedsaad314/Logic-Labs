/*
 * Problem: Storing plaintext passwords is a catastrophic security failure. If a database 
 * is breached, every user account is compromised instantly.
 * Logic: We never store the password. Instead, we generate a random "Salt" (unique string), 
 * append it to the password, and run it through a one-way Hashing algorithm. To verify a login, 
 * we hash the inputted password with the stored salt and compare the resulting hashes.
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>

using namespace std;

#define BOLD "\033[1m"
#define GRAY "\033[90m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

struct UserRecord {
    string salt;
    unsigned long storedHash;
};

class SecurityVault {
private:
    unordered_map<string, UserRecord> database;

    // Simple pseudo-random salt generator
    string generateSalt() {
        string salt = "";
        string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%";
        srand(time(0));
        for (int i = 0; i < 8; i++) salt += chars[rand() % chars.length()];
        return salt;
    }

    // djb2 hash algorithm (simplified for demonstration)
    unsigned long hashString(string str) {
        unsigned long hash = 5381;
        for (char c : str) hash = ((hash << 5) + hash) + c; 
        return hash;
    }

public:
    void registerUser(string username, string password) {
        if (database.find(username) != database.end()) {
            cout << "  " << RED << "[-] User already exists." << RESET << "\n";
            return;
        }
        string salt = generateSalt();
        unsigned long hash = hashString(password + salt);
        
        database[username] = {salt, hash};
        cout << "  " << GREEN << "[+] Registered successfully." << RESET << "\n";
        cout << "  " << GRAY << "Generated Salt: " << salt << RESET << "\n";
        cout << "  " << GRAY << "Stored Hash:    " << hash << RESET << "\n";
    }

    void authenticateUser(string username, string password) {
        if (database.find(username) == database.end()) {
            cout << "  " << RED << "[!] Access Denied: User not found." << RESET << "\n";
            return;
        }
        
        UserRecord record = database[username];
        unsigned long attemptHash = hashString(password + record.salt);
        
        if (attemptHash == record.storedHash) {
            cout << "  " << GREEN << "[✓] Access Granted: Identity verified." << RESET << "\n";
        } else {
            cout << "  " << RED << "[!] Access Denied: Invalid password." << RESET << "\n";
        }
    }
};

int main() {
    SecurityVault vault;
    cout << BOLD << "\n--- Identity & Security Vault ---" << RESET << "\n";
    cout << GRAY << "Commands:" << RESET << "\n";
    cout << GRAY << "  reg <user> <pass>   (e.g., reg Saad admin123)" << RESET << "\n";
    cout << GRAY << "  login <user> <pass> (e.g., login Saad admin123)" << RESET << "\n";
    cout << GRAY << "  exit" << RESET << "\n\n";

    string cmd, user, pass;
    while (true) {
        cout << BOLD << "Auth > " << RESET;
        cin >> cmd;
        if (cmd == "exit") break;

        cin >> user >> pass;
        if (cmd == "reg") vault.registerUser(user, pass);
        else if (cmd == "login") vault.authenticateUser(user, pass);
        else cout << "  " << RED << "Invalid command." << RESET << "\n";
    }
    return 0;
}