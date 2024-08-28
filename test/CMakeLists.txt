cmake_minimum_required(VERSION 3.28)
project(TodoList)

# Include GoogleTest
add_subdirectory(lib/googletest-main)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Set source files for testing
set(TEST_SOURCE_FILES
        Attivita_test.cpp
        TodoList_test.cpp
        runAllTest.cpp
)

# Create the test executable
add_executable(TodoList_Test ${TEST_SOURCE_FILES})

# Link GoogleTest libraries to the test executable
target_link_libraries(TodoList_Test gtest gtest_main)

# target_link_libraries(TodoList_Test core)