cmake_minimum_required(VERSION 3.28)
project(TodoList)

# Find and include wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

# Add the main project executable
add_executable(TodoList
        main.cpp
        Attivita.h
        TodoList.h
        MyApp.h
        MyApp.cpp
        MyFrame.h
        MyFrame.cpp
        test/Attivita_test.cpp)

# Link wxWidgets libraries to the main executable
target_link_libraries(TodoList ${wxWidgets_LIBRARIES})

# Enable testing
enable_testing()

# Add GoogleTest as a subdirectory (assumes GoogleTest is in the 'test' directory)
add_subdirectory(test)

# Add the test executable
add_executable(TodoList_Tests
        test/Attivita_test.cpp
        test/TodoList_test.cpp
        test/runAllTest.cpp
)

# Link GoogleTest libraries to the test executable
target_link_libraries(TodoList_Tests gtest gtest_main)

# Register the test executable with CMake
add_test(NAME TodoList_Tests COMMAND TodoList_Tests)