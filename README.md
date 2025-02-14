# Multi-threaded element queue project (C++/Cmake)

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
```

### Install C++ compiler and CMake
```sh
sudo apt update && sudo apt install build-essential cmake ninja-build pkg-config clang-tidy cppcheck valgrind
```
### Install Doxygen for documentation
```sh
sudo apt install -y doxygen graphviz
```
### Install testing frameworks
```sh
sudo apt install -y libgtest-dev cmake
sudo apt install -y libcppunit-dev
sudo apt install -y catch2
```
## **Building the project**
Download the project or git clone

Run the following commands:
```sh
mkdir build && cd build
cmake ..
make -j$(nproc)
```
## **Building the documentation**
If you are in root folder, move to build folder:
```sh
cd build
```
Then:
```sh
make doc
cd ..
xdg-open docs/html/index.html
```

## **Testing**
To run the template:
```sh
./template
```
To run all tests:
```sh
ctest --output-on-failure
```
To run one by one:
```sh
./test_gtest      # run gtest test
./test_cppunit    # run cppunit test
./test_catch      # run catch test
```
