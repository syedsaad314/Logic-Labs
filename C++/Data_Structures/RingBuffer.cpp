/*
 * Problem: Standard queues use mutex locks to prevent threads from colliding, 
 * but locks cause massive latency in high-frequency data streaming.
 * Logic: A Circular Array (Ring Buffer) using atomic operations. One thread writes, 
 * another reads, and they chase each other around the circle without ever locking.
 */

#include <iostream>
#include <atomic>
#include <vector>
#include <thread>

using namespace std;

template<typename T, size_t Size>
class LockFreeRingBuffer {
private:
    T buffer[Size];
    atomic<size_t> head{0};
    atomic<size_t> tail{0};

public:
    bool push(const T& item) {
        size_t currentTail = tail.load(memory_order_relaxed);
        size_t nextTail = (currentTail + 1) % Size;
        
        if (nextTail == head.load(memory_order_acquire)) {
            return false; // Buffer is full
        }
        
        buffer[currentTail] = item;
        tail.store(nextTail, memory_order_release);
        return true;
    }

    bool pop(T& item) {
        size_t currentHead = head.load(memory_order_relaxed);
        
        if (currentHead == tail.load(memory_order_acquire)) {
            return false; // Buffer is empty
        }
        
        item = buffer[currentHead];
        head.store((currentHead + 1) % Size, memory_order_release);
        return true;
    }
};

int main() {
    cout << "\033[1m\n--- Lock-Free Ring Buffer ---\033[0m\n";
    LockFreeRingBuffer<int, 5> stream;
    
    stream.push(101);
    stream.push(102);
    cout << "  \033[32m[Write]\033[0m Pushed data to ring buffer.\n";

    int data;
    while(stream.pop(data)) {
        cout << "  \033[36m[Read]\033[0m Consumed: " << data << "\n";
    }
    return 0;
}