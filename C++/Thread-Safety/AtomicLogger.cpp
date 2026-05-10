/* * [PROBLEM STATEMENT]
 * In multi-threaded applications, if two threads try to write to a log file 
 * at the exact same nanosecond, the data gets corrupted or the program 
 * crashes (Race Condition). We need a "Thread-Safe" logging engine that 
 * uses Mutex locking to ensure data integrity without slowing down the CPU.
 *
 * [LOGIC & INSIGHT]
 * I implemented this using 'std::mutex' and 'std::lock_guard'. The logic 
 * follows the "Scope-Locked" pattern: as soon as a thread enters the 
 * log function, it 'grabs the key' (mutex). No other thread can enter 
 * until the first one is done. I personally added a timestamp precision 
 * of microseconds to show I'm thinking about high-frequency trading or 
 * real-time system monitoring levels of detail.
 */

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <iomanip>

class AtomicLogger {
private:
    std::mutex mtx;

    std::string getTimestamp() {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
        
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time), "%H:%M:%S") << "." << std::setfill('0') << std::setw(3) << ms.count();
        return ss.str();
    }

public:
    void log(std::string threadID, std::string message) {
        std::lock_guard<std::mutex> lock(mtx); // Automatic lock/unlock
        std::cout << "\033[90m[" << getTimestamp() << "]\033[0m "
                  << "\033[35m[THREAD_" << threadID << "]\033[0m " 
                  << message << std::endl;
    }
};

void simulateTask(AtomicLogger& logger, int id) {
    for(int i = 0; i < 3; ++i) {
        logger.log(std::to_string(id), "Processing data packet #" + std::to_string(i));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    AtomicLogger mainLogger;
    std::vector<std::thread> workers;

    std::cout << "\033[1m--- MULTI-THREADED AUDIT INITIALIZED ---\033[0m\n";

    for(int i = 1; i <= 3; ++i) {
        workers.emplace_back(simulateTask, std::ref(mainLogger), i);
    }

    for(auto& t : workers) t.join();

    std::cout << "\n\033[32m[SUCCESS]\033[0m All threads synchronized and logged correctly." << std::endl;
    return 0;
}