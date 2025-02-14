#include "Queue.h"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <thread>
#include <chrono>
#include <cppunit/ui/text/TestRunner.h>

/**
 * @brief Test suite for the Queue class using CppUnit.
 */
class QueueTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(QueueTest);
    CPPUNIT_TEST(testPushPop);
    CPPUNIT_TEST(testOverflow);
    CPPUNIT_TEST(testTimeout);
    CPPUNIT_TEST(testMultiThread);
    CPPUNIT_TEST_SUITE_END();

public:
    /**
     * @brief Tests basic push and pop operations.
     * 
     * Inserts three elements and ensures they are retrieved in FIFO order.
     */
    void testPushPop() {
        Queue<int> q(3);
        q.Push(10);
        q.Push(20);
        q.Push(30);
        
        CPPUNIT_ASSERT(q.Pop() == 10);
        CPPUNIT_ASSERT(q.Pop() == 20);
        CPPUNIT_ASSERT(q.Pop() == 30);
    }

    /**
     * @brief Tests queue overflow behavior.
     * 
     * Pushes three elements into a queue of size 2, ensuring the oldest element is dropped.
     */
    void testOverflow() {
        Queue<int> q(2);
        q.Push(1);
        q.Push(2);
        q.Push(3);
        
        CPPUNIT_ASSERT(q.Pop() == 2);
        CPPUNIT_ASSERT(q.Pop() == 3);
    }

    /**
     * @brief Tests the timeout behavior when popping from an empty queue.
     * 
     * Expects a runtime error to be thrown if no elements are available within the timeout period.
     */
    void testTimeout() {
        Queue<int> q(2);

        try {
            q.PopWithTimeout(100);
            CPPUNIT_FAIL("Error");
        } catch (const std::runtime_error& e) {
            CPPUNIT_ASSERT_EQUAL(std::string("Timeout reached, no element available"), std::string(e.what()));
        }
    }

    /**
     * @brief Tests the queue in a multi-threaded environment.
     * 
     * Starts a writer thread that pushes values into the queue and a reader thread that retrieves them.
     * Ensures that the values are within the expected range.
     */
    void testMultiThread() {
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
                CPPUNIT_ASSERT(val >= 0 && val <= 4);
            }
        });

        writer.join();
        reader.join();
    }
};

/**
 * @brief Main function that runs the CppUnit test suite.
 * 
 * Registers the QueueTest suite and executes all defined test cases.
 * @return 0 if all tests pass, 1 if any test fails.
 */
int main() {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());

    runner.addTest(QueueTest::suite());

    return runner.run() ? 0 : 1;
}

CPPUNIT_TEST_SUITE_REGISTRATION(QueueTest);