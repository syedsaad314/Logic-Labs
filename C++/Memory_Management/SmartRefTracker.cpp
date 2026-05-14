/* * [PROBLEM STATEMENT]
 * In large C++ applications, tracking which part of the system is still 
 * using a specific memory block is a nightmare. If we delete it too early, 
 * the app crashes; if we don't delete it, we have a memory leak. 
 *
 * [LOGIC & INSIGHT]
 * I decided to build a "Lightweight Reference Tracker." Instead of just 
 * a pointer, I’m wrapping it in a class that manages a 'Reference Count'. 
 * Every time a new part of the code "borrows" the data, the count goes up. 
 * When they're done, it goes down. The moment it hits zero, the memory 
 * is automatically freed. It’s essentially a DIY 'shared_ptr' that allows 
 * me to see exactly who is holding onto what in real-time.
 */

#include <iostream>
#include <string>

class Tracker {
private:
    int* refCount;
    std::string resourceName;

public:
    Tracker(std::string name) : resourceName(name) {
        refCount = new int(1);
        std::cout << "\033[1;32m[INIT]\033[0m Resource '" << resourceName << "' spawned. Refs: 1" << std::endl;
    }

    // Copy Constructor - incrementing the count
    Tracker(const Tracker& other) {
        this->refCount = other.refCount;
        this->resourceName = other.resourceName;
        (*refCount)++;
        std::cout << "\033[1;36m[BORROW]\033[0m Resource '" << resourceName << "' shared. Current Refs: " << *refCount << std::endl;
    }

    ~Tracker() {
        (*refCount)--;
        if (*refCount == 0) {
            delete refCount;
            std::cout << "\033[1;31m[PURGE]\033[0m Zero references left. '" << resourceName << "' cleared from memory." << std::endl;
        } else {
            std::cout << "\033[1;33m[DETACH]\033[0m One ref dropped for '" << resourceName << "'. Remaining: " << *refCount << std::endl;
        }
    }

    void status() {
        std::cout << "  -> Tracking: " << resourceName << " | Health: STABLE" << std::endl;
    }
};

int main() {
    std::cout << "--- LOGIC LAB: MEMORY AUDIT ---" << std::endl;
    {
        Tracker core("NETWORK_BUFFER_ALPHA");
        core.status();
        {
            Tracker backup = core; // Borrowing
            backup.status();
        } // Backup out of scope
    } // Core out of scope
    return 0;
}