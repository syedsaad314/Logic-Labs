/*
 * Problem: Manual memory management (new/delete) is the #1 cause of memory leaks 
 * and "Dangling Pointer" crashes in high-performance C++ systems.
 * Logic: RAII (Resource Acquisition Is Initialization). We use std::unique_ptr 
 * and std::shared_ptr to automate memory cleanup. When the object goes out of scope, 
 * the memory is instantly reclaimed by the system—no manual delete required.
 */

#include <iostream>
#include <memory>
#include <string>

class NetworkBuffer {
public:
    NetworkBuffer(std::string id) : bufferId(id) { std::cout << "  \033[32m[Alloc]\033[0m Buffer " << bufferId << " created.\n"; }
    ~NetworkBuffer() { std::cout << "  \033[31m[Dealloc]\033[0m Buffer " << bufferId << " destroyed automatically.\n"; }
    void process() { std::cout << "  \033[36m[Compute]\033[0m Processing data in " << bufferId << "...\n"; }
private:
    std::string bufferId;
};

int main() {
    std::cout << "\033[1m\n--- Smart Pointer Resource Manager ---\033[0m\n";

    {
        // unique_ptr: Exclusive ownership. No one else can point to this.
        std::unique_ptr<NetworkBuffer> secureBuf = std::make_unique<NetworkBuffer>("SECURE_001");
        secureBuf->process();
    } // secureBuf is automatically deleted here

    std::cout << "\033[90mScope closed. Checking memory safety...\033[0m\n";
    return 0;
}