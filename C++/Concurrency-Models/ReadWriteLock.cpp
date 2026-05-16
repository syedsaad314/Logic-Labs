/* * [PROBLEM STATEMENT]
 * Standard Mutexes lock out EVERYONE. If 100 threads just want to 'Read' 
 * data and only 1 wants to 'Write', a standard Mutex forces the 100 readers 
 * to wait in a single-file line. This destroys performance in high-traffic systems.
 *
 * [LOGIC & INSIGHT]
 * I implemented a 'Shared Mutex' (Read-Write Lock) algorithm. Multiple 
 * threads can acquire the "Read Lock" simultaneously without blocking each 
 * other. But the moment a thread requests the "Write Lock", it ensures 
 * exclusive access to prevent data corruption. This is the exact synchronization 
 * primitive used in enterprise database engines.
 */

#include <iostream>
#include <thread>
#include <shared_mutex>
#include <vector>
#include <chrono>

class ThreadSafeCache {
private:
    std::string cachedData = "INIT_STATE";
    mutable std::shared_mutex rw_mutex;

public:
    void readData(int threadID) {
        std::shared_lock<std::shared_mutex> lock(rw_mutex); // Shared lock
        std::cout << "\033[90m[READ]\033[0m Thread " << threadID << " accessing: " << cachedData << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    void writeData(int threadID, std::string newData) {
        std::unique_lock<std::shared_mutex> lock(rw_mutex); // Exclusive lock
        std::cout << "\033[31m[WRITE]\033[0m Thread " << threadID << " updating data to: \033[32m" << newData << "\033[0m\n";
        cachedData = newData;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
};

void runSimulation() {
    ThreadSafeCache cache;
    std::vector<std::thread> workers;

    std::cout << "\033[1m--- CONCURRENCY ENGINE BOOT --- \033[0m\n";

    // 5 Readers, 1 Writer simulating heavy read-traffic
    for (int i = 1; i <= 5; ++i) workers.emplace_back(&ThreadSafeCache::readData, &cache, i);
    workers.emplace_back(&ThreadSafeCache::writeData, &cache, 99, "ALPHA_CONFIG_LOADED");
    for (int i = 6; i <= 10; ++i) workers.emplace_back(&ThreadSafeCache::readData, &cache, i);

    for (auto& t : workers) t.join();
}

int main() {
    runSimulation();
    return 0;
}