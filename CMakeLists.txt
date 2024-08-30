cmake_minimum_required(VERSION 3.28)
project(TodoList)

# Add GoogleTest as a subdirectory
add_subdirectory(test/lib/googletest-main)

# Include the GoogleTest include directories
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Add the main executable
add_executable(TodoList main.cpp MyFrame.cpp MyApp.cpp)

# Link wxWidgets libraries
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})
target_link_libraries(TodoList ${wxWidgets_LIBRARIES})

# Add the test executable
add_executable(TodoList_Test
        test/Attivita_test.cpp
        test/TodoList_test.cpp
)

# Link GoogleTest and wxWidgets libraries to the test executable
target_link_libraries(TodoList_Test gtest gtest_main ${wxWidgets_LIBRARIES})

# Enable testing
enable_testing()

# Add tests
add_test(NAME AttivitaTest COMMAND TodoList_Test)