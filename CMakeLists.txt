cmake_minimum_required(VERSION 3.22)
project(pelageia-immersive)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME} main.cpp
        Core/Utils/Config/ConfigLoader.cpp
        Core/Utils/Config/ConfigLoader.h
        Core/Utils/Parser/TryParse.cpp
        Core/Utils/Parser/TryParse.h
        Core/Utils/Logger/PeImLogger.cpp
        Core/Engine.cpp
        Core/Engine.h
        Core/Graphics/TextureManager.cpp
        Core/Graphics/TextureManager.h
        Core/Graphics/TextureManager.h
        Core/Physics/Vector2D.h
        Core/Physics/Vector2D.h
        Core/Physics/Transform.h
        Core/Objects/IObject.h
        Core/Objects/GameObject.h
        Core/Characters/Character.h
        Core/Characters/Player.cpp
        Core/Characters/Player.h
        Core/Objects/Utils.h
        Core/Physics/RigidBody.h
        Core/Animation/Animation.cpp
        Core/Animation/Animation.h
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




