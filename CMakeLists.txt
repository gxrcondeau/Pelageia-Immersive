cmake_minimum_required(VERSION 3.22)
project(pelageia-immersive)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME} main.cpp
        Core/Engine.cpp
        Core/Engine.h
        Core/Utils/ConfigLoader.cpp
        Core/Utils/ConfigLoader.h
        Core/Game.cpp
        Core/Game.h
        Core/Graphics/Graphics.cpp
        Core/Graphics/Graphics.h
        Core/Graphics/Image.cpp
        Core/Graphics/Image.h
)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/SDL2IMAGE/cmake)
set(SDL2_PATH "SDL2/x86_64-w64-mingw32")
set(SDL2IMAGE_PATH "SDL2IMAGE/x86_64-w64-mingw32")

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})


# Find SDL_image
# find_package(SDL2IMAGE REQUIRED)
# include_directories(${PROJECT_NAME} ${SDL2IMAGE_INCLUDE_DIRS})
# target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2IMAGE_LIBRARIES})