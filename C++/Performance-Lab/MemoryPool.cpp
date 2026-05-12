/* * [PROBLEM STATEMENT]
 * Frequent 'new' and 'delete' calls in C++ cause memory fragmentation and 
 * high latency due to OS-level system calls. In high-performance systems 
 * like game engines or trading platforms, we need a "Memory Pool" that 
 * pre-allocates a large chunk of memory and manages it manually.
 *
 * [LOGIC & INSIGHT]
 * I implemented a 'Slab-based' allocator. Instead of asking the OS for 
 * memory every time, I grab a large block once. The 'allocate' function 
 * simply moves a pointer forward, and 'reset' clears everything in constant 
 * time (O(1)). I personally added a "High-Water Mark" tracker to log the 
 * peak memory usage—this is crucial for profiling resource-heavy modules 
 * without using external tools.
 */

#include <iostream>
#include <vector>
#include <chrono>

class MemoryPool {
private:
    char* pool;
    size_t totalSize;
    size_t usedSize;
    size_t peakUsage;

public:
    MemoryPool(size_t size) : totalSize(size), usedSize(0), peakUsage(0) {
        pool = new char[size];
        std::cout << "\033[1m[POOL_INIT]\033[0m Pre-allocated " << size << " bytes." << std::endl;
    }

    ~MemoryPool() { delete[] pool; }

    void* allocate(size_t size) {
        if (usedSize + size > totalSize) {
            std::cerr << "\033[31m[ERROR]\033[0m Memory Pool Exhausted!" << std::endl;
            return nullptr;
        }
        void* ptr = pool + usedSize;
        usedSize += size;
        if (usedSize > peakUsage) peakUsage = usedSize;
        return ptr;
    }

    void reset() {
        std::cout << "\033[36m[RESET]\033[0m Reclaiming " << usedSize << " bytes. Peak was: " << peakUsage << std::endl;
        usedSize = 0;
    }

    void status() {
        double percent = (static_cast<double>(usedSize) / totalSize) * 100;
        std::cout << "  \033[32m[STATUS]\033[0m Usage: " << usedSize << "/" << totalSize 
                  << " (" << percent << "%)" << std::endl;
    }
};

int main() {
    MemoryPool labMemory(1024); // 1KB Pool

    labMemory.status();
    
    // Simulating allocation of 100 integers
    int* arr = (int*)labMemory.allocate(100 * sizeof(int));
    if(arr) {
        for(int i=0; i<10; i++) arr[i] = i * 7;
        std::cout << "  \033[34m[DATA]\033[0m First index value: " << arr[0] << std::endl;
    }

    labMemory.status();
    labMemory.reset();
    return 0;
}