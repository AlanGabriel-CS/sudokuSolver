cmake_minimum_required(VERSION 3.10)

project(SudokuServer)

set(CMAKE_CXX_STANDARD 14)

# Include the C++ REST SDK (cpprestsdk)
find_package(cpprestsdk REQUIRED)

add_executable(SudokuServer main.cpp)

target_link_libraries(SudokuServer PRIVATE cpprest)
