/* * [PROBLEM STATEMENT]
 * In high-performance C++ systems, memory leaks and "Double Free" errors are the 
 * leading causes of system crashes. Standard smart pointers are great, but for 
 * custom hardware interfaces, we often need a "Resource Gatekeeper" that manages 
 * memory with custom allocation policies and logging for audit trails.
 *
 * [LOGIC & INSIGHT]
 * I designed this 'ResourceShield' using a Template-based Wrapper. It uses a 
 * "RAII" (Resource Acquisition Is Initialization) pattern. My personal addition 
 * is the 'Audit Trail'—every time memory is accessed or released, the system 
 * logs the state. This makes debugging complex pointer arithmetic significantly 
 * easier because the memory 'talks' to you.
 */

#include <iostream>
#include <string>
#include <memory>
#include <vector>

template <typename T>
class ResourceShield {
private:
    T* data;
    std::string resourceID;
    static int activeAllocations;

public:
    // Constructor with resource tracking
    ResourceShield(T* rawData, std::string id) : data(rawData), resourceID(id) {
        activeAllocations++;
        std::cout << "\033[32m[ALLOCATED]\033[0m Resource: " << resourceID 
                  << " | Global Pool: " << activeAllocations << std::endl;
    }

    // Destructor ensures no memory leak
    ~ResourceShield() {
        delete data;
        activeAllocations--;
        std::cout << "\033[31m[RELEASED]\033[0m Resource: " << resourceID 
                  << " | Remaining Pool: " << activeAllocations << std::endl;
    }

    void inspect() {
        if (data) {
            std::cout << "  \033[34m[INSPECTION]\033[0m ID: " << resourceID 
                      << " | Current Value: " << *data << std::endl;
        }
    }

    // Overloading arrow operator for seamless pointer behavior
    T* operator->() { return data; }
};

template <typename T>
int ResourceShield<T>::activeAllocations = 0;

int main() {
    std::cout << "--- STARTING SYSTEM MEMORY AUDIT ---\n" << std::endl;

    {
        ResourceShield<int> coreModule(new int(1024), "CORE_AUTH_BUFFER");
        coreModule.inspect();

        ResourceShield<std::string> netModule(new std::string("SSH_ENCRYPT_KEY_v2"), "NETWORK_KEY_STORE");
        std::cout << "  \033[36m[DATA]\033[0m Content: " << *netModule.operator->() << std::endl;
    } 

    std::cout << "\n--- AUDIT COMPLETE: ALL BLOCKS PURGED ---" << std::endl;
    return 0;
}