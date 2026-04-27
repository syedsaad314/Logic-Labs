/*
 * Problem: Writing millions of log entries directly to a disk synchronously blocks the main 
 * execution thread, bringing high-frequency APIs to a complete halt.
 * Logic: Stream Buffering. Instead of writing to the disk on every single log call, we write 
 * to a memory buffer. Once the buffer hits a specific threshold (e.g., 4KB), it flushes to 
 * the disk in one massive, highly efficient I/O operation.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class BufferedLogger {
private:
    ofstream logFile;
    vector<string> buffer;
    size_t flushThreshold;

    void flush() {
        if (buffer.empty()) return;
        for (const string& log : buffer) {
            logFile << log << "\n";
        }
        logFile.flush();
        cout << "  \033[90m[Disk I/O]\033[0m Flushed " << buffer.size() << " records to disk.\n";
        buffer.clear();
    }

public:
    BufferedLogger(const string& filename, size_t threshold = 5) : flushThreshold(threshold) {
        logFile.open(filename, ios::app);
    }

    ~BufferedLogger() {
        flush(); // Ensure remaining logs are written on shutdown
        logFile.close();
    }

    void log(const string& level, const string& message) {
        string entry = "[" + level + "] " + message;
        buffer.push_back(entry);
        
        cout << "  \033[36m[Memory]\033[0m Cached in RAM: " << entry << "\n";

        if (buffer.size() >= flushThreshold) {
            flush();
        }
    }
};

int main() {
    cout << "\033[1m\n--- Buffered Stream Logger ---\033[0m\n";
    BufferedLogger sysLog("system_metrics.log", 3); // Flushes every 3 logs

    sysLog.log("INFO", "Server initialized on port 8080");
    sysLog.log("DEBUG", "Database connection pool established");
    sysLog.log("WARN", "High memory usage detected in cache layer"); 
    // Buffer hits threshold here, flushes to disk.
    
    sysLog.log("ERROR", "Connection timeout on Node 2");
    
    return 0;
}