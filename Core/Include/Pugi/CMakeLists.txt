cmake_minimum_required(VERSION 3.26)

project(Pugixml)

set(SOURCE_LIB pugixml.cpp)

add_library(Pugixml STATIC ${SOURCE_LIB})