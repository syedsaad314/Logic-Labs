/*
 * Problem: Multiple sensors (threads) are writing data at the same time the system 
 * is trying to read it. Without synchronization, the data corrupts and the app crashes.
 * Logic: The Producer-Consumer Pattern. We use a std::mutex to lock the queue during 
 * writes/reads, and a std::condition_variable to put the reader to "sleep" when the 
 * queue is empty, saving 100% of CPU cycles that would be wasted polling.
 */

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class MetricQueue {
private:
    queue<int> dataQueue;
    mutex mtx;
    condition_variable cv;

public:
    void produce(int metric) {
        {
            lock_guard<mutex> lock(mtx);
            dataQueue.push(metric);
            cout << "  \033[32m[Sensor]\033[0m Logged metric: " << metric << "\n";
        }
        cv.notify_one(); // Wake up the consumer
    }

    void consume() {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this]() { return !dataQueue.empty(); }); // Sleep until data arrives
        
        int metric = dataQueue.front();
        dataQueue.pop();
        cout << "  \033[36m[Processor]\033[0m Handled metric: " << metric << "\n";
    }
};

int main() {
    cout << "\033[1m\n--- Thread-Safe Metric Queue ---\033[0m\n";
    MetricQueue mq;

    thread producer([&]() { for(int i=1; i<=3; i++) { mq.produce(i * 100); this_thread::sleep_for(chrono::milliseconds(100)); } });
    thread consumer([&]() { for(int i=1; i<=3; i++) { mq.consume(); } });

    producer.join();
    consumer.join();
    return 0;
}