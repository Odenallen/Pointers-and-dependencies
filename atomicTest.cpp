#include <iostream>
#include <atomic>
#include <thread>



std::atomic<int> counter(0);

void incrementCounter() {
    for (int i = 0; i < 10000; ++i) {
        counter.fetch_add(1);
    }
}

int main() {
    std::thread t1(incrementCounter);
    std::thread t2(incrementCounter);

    t1.join();
    t2.join();

    std::cout << "Counter value: " << counter << std::endl;

    return 0;
}
