cmake_minimum_required(VERSION 3.10)
project(CrossArray)

set(CMAKE_CXX_STANDARD 14)

# Find all cpp files in the directory
file(GLOB SOURCES "*.cpp")

# If there are no cpp files, create a dummy one so cmake doesn't fail
if(NOT SOURCES)
    file(WRITE dummy.cpp "int main() { return 0; }")
    set(SOURCES dummy.cpp)
endif()

add_executable(code ${SOURCES})
