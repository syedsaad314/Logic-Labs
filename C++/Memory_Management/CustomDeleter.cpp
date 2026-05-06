/*
 * Problem: Sometimes resources aren't just memory (e.g., File handles, Database connections). 
 * A standard smart pointer doesn't know how to "close" a file or "log off" a session.
 * Logic: Custom Deleters. We provide a lambda function to the unique_ptr. When the 
 * pointer goes out of scope, it executes our custom logic (like closing a log file) 
 * before freeing the memory.
 */

#include <iostream>
#include <memory>

void closeSystemLog(int* logHandle) {
    std::cout << "  \033[31m[System Cleanup]\033[0m Closing log handle #" << *logHandle << " and flushing buffers.\n";
    delete logHandle;
}

int main() {
    std::cout << "\033[1m\n--- Custom Resource Deleter ---\033[0m\n";
    {
        std::unique_ptr<int, decltype(&closeSystemLog)> smartLog(new int(101), closeSystemLog);
        std::cout << "  \033[32m[Active]\033[0m Logging session active for ID: " << *smartLog << "\n";
    } 
    return 0;
}