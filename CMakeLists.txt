cmake_minimum_required(VERSION 3.22)
project(pelageia-immersive)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME} main.cpp
        Core/Engine.cpp
        Core/Engine.h
        Core/Utils/ConfigLoader.cpp
        Core/Utils/ConfigLoader.h
)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2/x86_64-w64-mingw32")

find_package(tinyxml2 CONFIG REQUIRED)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})