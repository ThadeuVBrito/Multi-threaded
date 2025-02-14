cmake_minimum_required(VERSION 3.10)
project(ThreadSafeQueue)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()

# Documentation
find_package(Doxygen REQUIRED)

set(DOXYGEN_INPUT_DIR ${CMAKE_SOURCE_DIR})
set(DOXYGEN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/docs)

add_custom_target(doc
    COMMAND doxygen ${CMAKE_SOURCE_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Doxygen documentation"
    VERBATIM
)

# Template
add_executable(template template.cpp)
target_include_directories(template PRIVATE ${CMAKE_SOURCE_DIR})

# gtest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(test_gtest test_queue_gtest.cpp)
target_link_libraries(test_gtest gtest gtest_main pthread)
add_test(NAME GTest_QueueTests COMMAND test_gtest)

# cppunit
find_package(PkgConfig REQUIRED)
pkg_check_modules(CPPUNIT REQUIRED cppunit)

include_directories(${CPPUNIT_INCLUDE_DIRS})
link_directories(${CPPUNIT_LIBRARY_DIRS})

add_executable(test_cppunit test_queue_cppunit.cpp)
target_link_libraries(test_cppunit ${CPPUNIT_LIBRARIES} pthread)
add_test(NAME CppUnit_QueueTests COMMAND test_cppunit)

# catch
find_package(Catch2 REQUIRED)

add_executable(test_catch test_queue_catch.cpp)
target_link_libraries(test_catch Catch2::Catch2WithMain)
add_test(NAME Catch2_QueueTests COMMAND test_catch)