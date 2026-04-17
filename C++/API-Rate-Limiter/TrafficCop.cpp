/*
 * Problem: If an API gets flooded with requests (DDoS attack or a viral moment), the server crashes. 
 * We need a mechanism to throttle incoming traffic fairly.
 * Logic: The "Token Bucket" algorithm. A bucket holds a maximum number of tokens and refills 
 * at a steady rate over time. Every request costs 1 token. If the bucket is empty, the request 
 * is aggressively denied (HTTP 429 Too Many Requests).
 */

#include <iostream>
#include <chrono>
#include <thread>
#include <string>

using namespace std;
using namespace std::chrono;

#define BOLD "\033[1m"
#define GRAY "\033[90m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

class RateLimiter {
private:
    int maxTokens;
    double refillRatePerSecond;
    double currentTokens;
    time_point<steady_clock> lastRefillTime;

    void refill() {
        auto now = steady_clock::now();
        duration<double> elapsed = now - lastRefillTime;
        double tokensToAdd = elapsed.count() * refillRatePerSecond;
        
        if (tokensToAdd > 0) {
            currentTokens = min((double)maxTokens, currentTokens + tokensToAdd);
            lastRefillTime = now;
        }
    }

public:
    RateLimiter(int max, double rate) : maxTokens(max), refillRatePerSecond(rate), currentTokens(max) {
        lastRefillTime = steady_clock::now();
    }

    bool allowRequest() {
        refill();
        if (currentTokens >= 1.0) {
            currentTokens -= 1.0;
            return true;
        }
        return false;
    }

    int getAvailableTokens() {
        refill();
        return (int)currentTokens;
    }
};

int main() {
    cout << BOLD << "\n--- API Rate Limiter (Token Bucket) ---" << RESET << "\n";
    cout << GRAY << "Bucket Size: 5 tokens | Refill Rate: 1 token/sec" << RESET << "\n";
    cout << GRAY << "Press ENTER to send an API request. Type 'exit' to quit." << RESET << "\n\n";

    RateLimiter limiter(5, 1.0);
    string input;

    while (true) {
        cout << BOLD << "Client > " << RESET;
        getline(cin, input);
        if (input == "exit") break;

        if (limiter.allowRequest()) {
            cout << "  " << GREEN << "[200 OK]" << RESET << " Request processed. (Tokens left: " 
                 << limiter.getAvailableTokens() << ")\n";
        } else {
            cout << "  " << RED << "[429 TOO MANY REQUESTS]" << RESET << " Rate limit exceeded! Please wait.\n";
        }
    }
    return 0;
}