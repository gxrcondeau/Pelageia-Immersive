cmake_minimum_required(VERSION 3.22)
project(Vendor)

set(CMAKE_CXX_STANDARD 23)

set(SOURCES pugixml.cpp)

# Create a library from the source files
add_library(${PROJECT_NAME} PRIVATE ${SOURCES})

