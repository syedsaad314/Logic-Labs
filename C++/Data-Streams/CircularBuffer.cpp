/* * [PROBLEM STATEMENT]
 * In real-time systems (like audio processing or high-frequency trading), 
 * constantly allocating and deallocating memory is too slow. We need a 
 * "Fixed-Size Ring Buffer" that overwrites old data without shifting 
 * elements, maintaining O(1) performance for both reads and writes.
 *
 * [LOGIC & INSIGHT]
 * I designed this using a Template Class and a "Head/Tail" pointer logic. 
 * The trick is the modulo operator (%) which wraps the index back to zero 
 * when it hits the limit. I personally added a 'Fullness' check—if the 
 * buffer is full, it silently drops the oldest packet, ensuring the system 
 * never hangs. This is pure mechanical sympathy for the CPU.
 */

#include <iostream>
#include <vector>

template <typename T, size_t S>
class CircularBuffer {
private:
    T buffer[S];
    size_t head = 0;
    size_t tail = 0;
    bool full = false;

public:
    void push(T item) {
        buffer[head] = item;
        if (full) {
            tail = (tail + 1) % S; // Overwrite oldest
        }
        head = (head + 1) % S;
        full = head == tail;
    }

    T pop() {
        if (!full && head == tail) return T(); // Buffer empty
        T item = buffer[tail];
        full = false;
        tail = (tail + 1) % S;
        return item;
    }

    void debug() {
        std::cout << "\033[90m[BUFFER_STATE]\033[0m Head: " << head << " | Tail: " << tail << std::endl;
    }
};

int main() {
    CircularBuffer<int, 5> telemetry;
    
    std::cout << "--- INITIALIZING DATA STREAM ---\n";
    for(int i=1; i<=7; i++) {
        std::cout << "  Pushing Signal: " << i << "\n";
        telemetry.push(i);
    }
    
    telemetry.debug();
    std::cout << "\033[32m[RESULT]\033[0m Last Popped: " << telemetry.pop() << "\n";
    return 0;
}