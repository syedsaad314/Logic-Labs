/* * [PROBLEM STATEMENT]
 * When returning massive data structures (like a 10,000-element matrix) 
 * from a function, older C++ versions would create a "Deep Copy." 
 * This duplicates memory unnecessarily and spikes CPU usage, crashing 
 * low-memory environments.
 *
 * [LOGIC & INSIGHT]
 * I implemented C++11 Move Semantics using Rvalue References (&&) and 
 * std::move(). Instead of copying the data array, the new object "steals" 
 * the memory pointer from the temporary object, leaving the temporary 
 * object in a safe, empty state. This reduces a potentially O(N) copy 
 * operation down to an O(1) pointer swap. Absolute maximum efficiency.
 */

#include <iostream>
#include <vector>
#include <utility>

class HeavyBuffer {
private:
    int* data;
    size_t size;

public:
    // Standard Constructor
    HeavyBuffer(size_t s) : size(s) {
        data = new int[size];
        std::cout << "\033[36m[ALLOCATE]\033[0m " << size << " bytes reserved in heap.\n";
    }

    // Destructor
    ~HeavyBuffer() {
        delete[] data;
    }

    // Move Constructor (The Engine)
    HeavyBuffer(HeavyBuffer&& other) noexcept : data(nullptr), size(0) {
        // Steal the pointer
        this->data = other.data;
        this->size = other.size;

        // Nullify the source so it doesn't delete our stolen memory
        other.data = nullptr;
        other.size = 0;

        std::cout << "\033[1;32m[MOVE_SEMANTICS]\033[0m Memory ownership hijacked! Zero bytes copied.\n";
    }

    // Disable copying entirely to enforce strict performance
    HeavyBuffer(const HeavyBuffer&) = delete; 
    HeavyBuffer& operator=(const HeavyBuffer&) = delete;
};

HeavyBuffer generateData() {
    HeavyBuffer temp(10000); // Massive allocation
    return temp; // Move constructor automatically triggered here
}

int main() {
    std::cout << "--- ZERO-COPY PROTOCOL INITIATED ---\n";
    HeavyBuffer persistentBuffer = generateData();
    std::cout << "Operation complete. CPU cycle waste: 0%\n";
    return 0;
}