/*
 * Problem: Transmitting plain-text metrics over a network is a massive security risk.
 * Logic: A fast, lightweight XOR Cipher. It uses bitwise operations to scramble 
 * the data. It is extremely fast (zero memory overhead) and perfect for low-latency C++ systems.
 */

#include <iostream>
#include <string>

class CipherEngine {
private:
    char key = 'K'; // Super secret key

public:
    std::string process(std::string data) {
        std::string result = data;
        for (int i = 0; i < data.size(); i++) {
            result[i] = data[i] ^ key; // XOR bitwise operation
        }
        return result;
    }
};

int main() {
    std::cout << "\033[1m\n--- Bitwise Data Scrambler ---\033[0m\n";
    CipherEngine engine;
    
    std::string telemetry = "SERVER_LOAD_99%";
    std::cout << "  \033[90m[Original]\033[0m " << telemetry << "\n";

    std::string encrypted = engine.process(telemetry);
    std::cout << "  \033[31m[Encrypted]\033[0m " << encrypted << "\n";

    std::string decrypted = engine.process(encrypted); // XORing again decrypts it
    std::cout << "  \033[32m[Decrypted]\033[0m " << decrypted << "\n";

    return 0;
}