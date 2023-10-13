cmake_minimum_required(VERSION 3.26)

project(ConfigLoader)

set(SOURCE_LIB ConfigLoader.cpp)

add_library(ConfigLoader STATIC ${SOURCE_LIB})