/*
 * Problem: Using standard dynamic allocation (`new` and `delete`) in high-frequency trading 
 * or massive data loops causes severe heap fragmentation and unpredictable latency spikes.
 * Logic: Object Pooling. We pre-allocate a single, massive, contiguous block of memory 
 * when the server boots. Instead of asking the OS for memory, the application "borrows" 
 * pre-sized blocks from our pool in guaranteed O(1) time, eliminating fragmentation entirely.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class MemoryPool {
private:
    struct Block {
        bool inUse;
        int id;
    };
    
    vector<Block> pool;
    size_t totalBlocks;

public:
    MemoryPool(size_t size) : totalBlocks(size) {
        pool.resize(size);
        for (size_t i = 0; i < size; ++i) {
            pool[i] = {false, static_cast<int>(i)};
        }
        cout << "  \033[90m[System]\033[0m Pre-allocated contiguous memory pool of " << size << " blocks.\n";
    }

    int allocate() {
        for (size_t i = 0; i < totalBlocks; ++i) {
            if (!pool[i].inUse) {
                pool[i].inUse = true;
                cout << "  \033[32m[Allocated]\033[0m Block ID " << i << " assigned to process.\n";
                return i;
            }
        }
        cout << "  \033[31m[OOM Error]\033[0m Memory Pool exhausted.\n";
        return -1;
    }

    void deallocate(int blockId) {
        if (blockId >= 0 && blockId < totalBlocks && pool[blockId].inUse) {
            pool[blockId].inUse = false;
            cout << "  \033[36m[Freed]\033[0m Block ID " << blockId << " returned to pool.\n";
        } else {
            cout << "  \033[31m[Error]\033[0m Invalid block deallocation request.\n";
        }
    }
};

int main() {
    cout << "\033[1m\n--- High-Frequency Memory Pool Allocator ---\033[0m\n";
    cout << "\033[90mCommands: 'alloc', 'free <id>', 'exit'\033[0m\n\n";
    
    MemoryPool appPool(3); // Small pool for demonstration

    while (true) {
        cout << "\033[1mMemory Ops > \033[0m";
        string cmd;
        cin >> cmd;
        
        if (cmd == "exit") break;
        if (cmd == "alloc") appPool.allocate();
        else if (cmd == "free") {
            int id;
            cin >> id;
            appPool.deallocate(id);
        } else {
            cout << "  \033[31mInvalid command.\033[0m\n";
        }
    }
    return 0;
}