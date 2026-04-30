/*
 * Problem: Frequent reallocations of large strings or vectors cause the CPU to waste cycles 
 * copying data across the heap, leading to memory spikes and slow throughput.
 * Logic: Segmented Buffering. We use a chain of small, fixed-size memory blocks (segments). 
 * When one fills up, we attach a new one instead of resizing the whole buffer. This 
 * provides O(1) append time and prevents massive memory moves.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Segment {
    char data[1024];
    size_t used = 0;
};

class SegmentedBuffer {
private:
    vector<Segment*> chunks;
    
public:
    void append(const string& input) {
        if (chunks.empty() || chunks.back()->used + input.length() > 1024) {
            chunks.push_back(new Segment());
            cout << "  \033[90m[Memory]\033[0m New segment allocated.\n";
        }
        
        Segment* current = chunks.back();
        for (char c : input) {
            if (current->used < 1024) {
                current->data[current->used++] = c;
            }
        }
        cout << "  \033[32m[Append]\033[0m Added " << input.length() << " bytes.\n";
    }

    ~SegmentedBuffer() {
        for (auto s : chunks) delete s;
    }
};

int main() {
    cout << "\033[1m\n--- Segmented Stack Buffer ---\033[0m\n";
    SegmentedBuffer buffer;
    buffer.append("Initializing System Logs...");
    buffer.append("Stream Header: 0xAF441...");
    return 0;
}