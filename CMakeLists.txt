cmake_minimum_required(VERSION 3.22)
project(pelageia-immersive)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME} main.cpp
        Core/Game.cpp
        Core/Game.h
        Core/Graphics/Graphics.cpp
        Core/Graphics/Graphics.h
        Core/Graphics/Image.cpp
        Core/Graphics/Image.h
        Core/Utils/Config/ConfigLoader.cpp
        Core/Utils/Config/ConfigLoader.h
        Core/Utils/Parser/TryParse.cpp
        Core/Utils/Parser/TryParse.h
        Core/Input/Input.cpp
        Core/Input/Input.h
        Core/Utils/Logger/PeImLogger.cpp
)

include_directories(Core/Utils/ConfigLoader)
include_directories(Core/Include/Pugixml)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2/x86_64-w64-mingw32")
set(SDL2_IMAGE_PATH "SDL2/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES})




