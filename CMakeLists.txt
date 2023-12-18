cmake_minimum_required(VERSION 3.22)
project(pelageia-immersive)

set(CMAKE_CXX_STANDARD 23)

# Set the source files
set(SOURCES
        src/Engine.cpp
        src/systems/configuration/ConfigurationSystem.cpp
        src/systems/graphics/TextureManagerSystem.cpp
        src/systems/input/InputSystem.cpp
        src/systems/scene/SceneParserSystem.cpp
        src/components/scene/TileMapLayerComponent.cpp
)

include_directories(Vendor/Pugi)

# Create a library from the source files
add_library(${PROJECT_NAME} STATIC ${SOURCES})

# Set include directories for the library
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Organize source files into directories
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

# Create an executable for the main.cpp file
add_executable(pelageia_immersive_bin main.cpp)

# Set the C++ standard for the executable
set_target_properties(pelageia_immersive_bin PROPERTIES CXX_STANDARD 23)

# Link the executable with the library
target_link_libraries(pelageia_immersive_bin PRIVATE ${PROJECT_NAME})

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2/x86_64-w64-mingw32")
set(SDL2_IMAGE_PATH "SDL2/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})
