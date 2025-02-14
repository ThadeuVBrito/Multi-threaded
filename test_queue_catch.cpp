#define CATCH_CONFIG_MAIN
#include "Queue.h"
#include <catch2/catch_all.hpp>
#include <thread>
#include <chrono>

/**
 * @brief Tests the insertion and removal of elements in the queue.
 * 
 * Ensures that elements are inserted correctly and retrieved in FIFO order.
 */
TEST_CASE("Insertion and Remove Test", "[queue]") {
    Queue<int> q(3);

    SECTION("Insertion") {
        q.Push(10);
        q.Push(20);
        q.Push(30);
        REQUIRE(q.Count() == 3);
    }

    SECTION("Remove") {
        q.Push(10);
        q.Push(20);
        q.Push(30);

        REQUIRE(q.Pop() == 10);
        REQUIRE(q.Pop() == 20);
        REQUIRE(q.Pop() == 30);
        REQUIRE(q.Count() == 0);
    }
}

/**
 * @brief Tests the queue overflow behavior.
 * 
 * Inserts three elements into a queue of size 2, ensuring that the oldest element is discarded.
 */
TEST_CASE("Overflow - Oldest Element Dropped", "[queue]") {
    Queue<int> q(2);

    q.Push(1);
    q.Push(2);
    q.Push(3);

    REQUIRE(q.Pop() == 2);
    REQUIRE(q.Pop() == 3);
}

/**
 * @brief Tests the timeout behavior when trying to pop from an empty queue.
 * 
 * Expects a runtime exception if no elements are available within the timeout period.
 */
TEST_CASE("Timeout Test", "[queue]") {
    Queue<int> q(2);

    REQUIRE_THROWS_AS(q.PopWithTimeout(100), std::runtime_error);
}

/**
 * @brief Tests queue operations in a multithreaded environment.
 * 
 * Launches a writer thread that pushes elements and a reader thread that pops elements.
 * Ensures that the values retrieved are within the expected range.
 */
TEST_CASE("Multithreading", "[queue]") {
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
            REQUIRE(val >= 0);
            REQUIRE(val <= 4);
        }
    });

    writer.join();
    reader.join();
}
