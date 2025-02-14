#include <iostream>
#include <thread>
#include "Queue.h"

/**
 * @brief Function executed by the writer thread.
 * @param q Reference to the queue where elements will be inserted.
 * 
 * Pushes values into the queue while ensuring the behavior follows the provided example.
 */
void WriterThread(Queue<int>& q) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Small delay before starting

    q.Push(1);
    std::cout << "[Writer] Pushed(1)" << std::endl;
    q.PrintQueue();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    q.Push(2);
    std::cout << "[Writer] Pushed(2)" << std::endl;
    q.PrintQueue();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    q.Push(3);
    std::cout << "[Writer] Pushed(3)" << std::endl;
    q.PrintQueue();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    q.Push(4);
    std::cout << "[Writer] Pushed(4)" << std::endl;
    q.PrintQueue();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    q.Push(5);
    std::cout << "[Writer] Pushed(5)" << std::endl;
    q.PrintQueue();
}

/**
 * @brief Function executed by the reader thread.
 * @param q Reference to the queue from which elements will be retrieved.
 * 
 * Pops elements while following the expected sequence.
 */
void ReaderThread(Queue<int>& q) {
    std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // Ensure Writer starts first, forcing the overflow

    std::cout << "[Reader] Pop() -> " << q.Pop() << std::endl;
    q.PrintQueue();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::cout << "[Reader] Pop() -> " << q.Pop() << std::endl;
    q.PrintQueue();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::cout << "[Reader] Pop() -> " << q.Pop() << std::endl;
    q.PrintQueue();
}

/**
 * @brief Main function that initializes the queue and starts writer and reader threads.
 * 
 * Creates a queue with a maximum size of 2, then launches two separate threads:
 * - WriterThread: inserts values.
 * - ReaderThread: retrieves values.
 * 
 * Synchronization is handled using `join()`.
 * @return 0 on successful execution.
 */
int main() {
    Queue<int> q(2);
    
    std::thread writer(WriterThread, std::ref(q));
    std::thread reader(ReaderThread, std::ref(q));
    
    writer.join();
    reader.join();
    
    return 0;
}