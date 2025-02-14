# Thread-Safe Queue in C++

## Project Overview
This project implements a **thread-safe queue** in C++. The queue is designed to store **primitive data types** (e.g., `int`, `double`) and supports **blocking and timeout-based retrieval**.

### Features:
- **Thread-Safe Implementation**: Uses `std::mutex` and `std::condition_variable` to prevent race conditions.
- **Fixed Capacity with Overflow Handling**: Drops the oldest element when full.
- **Blocking & Timeout-Based `Pop()` Methods**:  
  - `Pop()` waits indefinitely if the queue is empty.  
  - `PopWithTimeout(milliseconds)` throws an exception after a given timeout.
- **Multi-threaded Testing**: Includes tests using **gtest, cppunit, and catch**.
- **CMake Build System**: Simplifies compilation and testing.
- **Doxygen Documentation**: Generates API documentation.

---

## **Installation & Setup**
Before running the project, ensure that you have the necessary dependencies installed.

### **Install Required Packages (Ubuntu/Debian)**
Run the following commands:
```sh
sudo apt update && sudo apt upgrade -y

# Install C++ compiler and CMake
sudo apt install -y g++ cmake

# Install Doxygen for documentation
sudo apt install -y doxygen graphviz

# Install testing frameworks
sudo apt install -y libgtest-dev cmake
sudo apt install -y libcppunit-dev
sudo apt install -y catch2

## **Building the project**
Download the project or git clone

Run the following commands:

mkdir build && cd build
cmake ..
make -j$(nproc)

## **Building the documentation**
If you are in root folder, move to build folder:

cd build

Then:

make doc
cd ..
xdg-open docs/html/index.html

## **Testing**
To run the template:
./template

To run all tests:

ctest --output-on-failure

To run one by one:
./test_gtest      # run gtest test
./test_cppunit    # run cppunit test
./test_catch      # run catch test
