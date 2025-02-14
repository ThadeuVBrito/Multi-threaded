#include "Queue.h"
#include <gtest/gtest.h>
#include <thread>
#include <chrono>

/**
 * @brief Tests basic push and pop operations.
 * 
 * Inserts three elements and verifies that they are retrieved in FIFO order.
 */
TEST(QueueTest, PushPopTest) {
    Queue<int> q(3);
    q.Push(10);
    q.Push(20);
    q.Push(30);
    
    EXPECT_EQ(q.Pop(), 10);
    EXPECT_EQ(q.Pop(), 20);
    EXPECT_EQ(q.Pop(), 30);
}

/**
 * @brief Tests queue overflow behavior.
 * 
 * Pushes three elements into a queue of size 2, ensuring the oldest element is dropped.
 */
TEST(QueueTest, OverflowTest) {
    Queue<int> q(2);
    q.Push(1);
    q.Push(2);
    q.Push(3);
    
    EXPECT_EQ(q.Pop(), 2);
    EXPECT_EQ(q.Pop(), 3);
}

/**
 * @brief Tests the timeout behavior when popping from an empty queue.
 * 
 * Expects a runtime error to be thrown if no elements are available within the timeout period.
 */
TEST(QueueTest, TimeoutTest) {
    Queue<int> q(2);
    
    EXPECT_THROW(q.PopWithTimeout(100), std::runtime_error);
}

/**
 * @brief Tests the queue in a multi-threaded environment.
 * 
 * Starts a writer thread that pushes values into the queue and a reader thread that retrieves them.
 * Ensures that the values are within the expected range.
 */
TEST(QueueTest, MultiThreadTest) {
    Queue<int> q(5);
    
    std::thread writer([&q]() {
        for (int i = 0; i < 5; i++) {
            q.Push(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    std::thread reader([&q]() {
        for (int i = 0; i < 5; i++) {
            int val = q.Pop();
            EXPECT_GE(val, 0);
            EXPECT_LE(val, 4);
        }
    });

    writer.join();
    reader.join();
}