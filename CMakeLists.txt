cmake_minimum_required(VERSION 3.28)
project(TodoList)

# Find and include wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

# Add the main project executable
add_executable(TodoList main.cpp
        Attivita.h)

# Link wxWidgets libraries to the main executable
target_link_libraries(TodoList ${wxWidgets_LIBRARIES})
