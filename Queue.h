#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H

#include <mutex>
#include <condition_variable>
#include <chrono>
#include <stdexcept>
#include <iostream>

/**
 * @class Queue
 * @brief Thread-safe queue implementation using dynamic memory allocation.
 * @tparam T Type of data stored in the queue.
 */
template <typename T>
class Queue {
private:
    T* queue;  ///< Dynamically allocated array for queue storage.
    std::mutex mtx;  ///< Mutex for thread safety.
    std::condition_variable cv;  ///< Condition variable for synchronization.
    int max_size;  ///< Maximum capacity of the queue.
    int front, rear, count;  ///< Indices and count of elements.

public:
    /**
     * @brief Constructs a queue with a defined maximum size.
     * @param size Maximum number of elements the queue can hold.
     */
    explicit Queue(int size) : max_size(size), front(0), rear(0), count(0) {
        queue = new T[max_size];  // Dynamic memory allocation
    }

    /**
     * @brief Pushes an element into the queue.
     * If the queue is full, the oldest element is overwritten.
     * @param element Element to be inserted.
     */
    void Push(T element) {
        std::unique_lock<std::mutex> lock(mtx);

        if (count >= max_size) { 
            // Overwrite the oldest element by advancing front
            front = (front + 1) % max_size;
            count--;
        }

        queue[rear] = element;
        rear = (rear + 1) % max_size;
        count++;

        cv.notify_one();  // Notify one waiting thread
    }

    /**
     * @brief Pops an element from the queue.
     * Blocks indefinitely if the queue is empty.
     * @return The removed element.
     */
    T Pop() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return count > 0; });

        T value = queue[front];
        front = (front + 1) % max_size;
        count--;

        return value;
    }

    /**
     * @brief Pops an element with a timeout.
     * @param milliseconds Maximum wait time before throwing an exception.
     * @return The removed element.
     * @throws std::runtime_error if timeout is exceeded.
     */
    T PopWithTimeout(int milliseconds) {
        std::unique_lock<std::mutex> lock(mtx);
        if (!cv.wait_for(lock, std::chrono::milliseconds(milliseconds), [this] { return count > 0; })) {
            throw std::runtime_error("Timeout reached, no element available");
        }

        T value = queue[front];
        front = (front + 1) % max_size;
        count--;

        return value;
    }

    /**
     * @brief Gets the current number of elements in the queue.
     * @return The number of elements currently stored.
     */
    int Count() {
        std::lock_guard<std::mutex> lock(mtx);
        return count;
    }

    /**
     * @brief Gets the maximum size of the queue.
     * @return The maximum number of elements the queue can hold.
     */
    int Size() {
        return max_size;
    }

    /**
     * @brief Prints the current elements in the queue.
     */
    void PrintQueue() {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "[Queue] Current state: [ ";
        for (int i = 0; i < count; i++) {
            std::cout << queue[(front + i) % max_size] << " ";
        }
        std::cout << "] (Size: " << count << "/" << max_size << ")" << std::endl;
    }

    /**
     * @brief Destructor to free dynamically allocated memory.
     */
    ~Queue() {
        delete[] queue;
    }
};

#endif // THREAD_SAFE_QUEUE_H