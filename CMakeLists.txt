cmake_minimum_required(VERSION 3.22)
project(pelageia-immersive)

set(CMAKE_CXX_STANDARD 23)

# Set the source files
set(SOURCES
        Private/Utils/Config/ConfigLoader.cpp
        Private/Engine.cpp
        Private/Graphics/TextureManager.cpp
        Private/Characters/Player.cpp
        Private/Animation/SpriteAnimation.cpp
        Private/Inputs/Input.cpp
        Private/Timer/Timer.cpp
        Private/Map/TileLayer.cpp
        Private/Map/TileMapParser.cpp
        Private/Camera/Camera.cpp
        Private/Collisions/CollisionHandler.cpp
        Private/Physics/Collider.cpp
        Private/Characters/Character.cpp
        Private/Graphics/ShadowManager.cpp
        Private/Animation/SeqAnimation.cpp
        Public/Map/EntitiesLayer.h
        Public/Utils/Calculations/Coordinates.h
        include/systems/graphics/TextureManagerSystem.h
        include/systems/configuration/ConfigurationSystem.h
        include/systems/input/InputSystem.h
        include/systems/scene/SceneParserSystem.h
        include/components/scene/LayerComponent.h
        include/components/sprite/SpriteComponent.h
        include/components/physics/TransformComponent.h
        include/components/physics/RigidBodyComponent.h
        include/components/BaseComponent.h
        include/entities/Entity.h
        include/systems/BaseSystem.h
        include/mathematics/Vector2D.h
        include/components/physics/ColliderComponent.h
        include/components/camera/CameraComponent.h
        include/components/animation/AnimationComponent.h
        include/components/animation/SpriteAnimationComponent.h
        include/entities/characters/CharacterEntity.h
        include/entities/characters/PlayerEntity.h
        include/entities/scene/GameMapEntity.h
        include/components/scene/TileLayerComponent.h
        include/components/scene/EntitiesLayerComponent.h
        include/mathematics/IsometricConverter.h
)

include_directories(Vendor/Pugi)

# Create a library from the source files
add_library(${PROJECT_NAME} STATIC ${SOURCES})

# Set include directories for the library
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Public)

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
