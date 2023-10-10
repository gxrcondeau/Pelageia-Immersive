# SDL2_image CMake version configuration file:
# This file is meant to be placed in a cmake subfolder of SDL2_image-devel-2.x.y-mingw

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(sdl2_image_config_path "../i686-w64-mingw32/lib/cmake/SDL2_image/sdl2_image-config-version.cmake")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(sdl2_image_config_path "../x86_64-w64-mingw32/lib/cmake/SDL2_image/sdl2_image-config-version.cmake")
else("${CMAKE_SIZEOF_VOID_P}" STREQUAL "")
    set(PACKAGE_VERSION_UNSUITABLE TRUE)
    return()
endif()

if(NOT EXISTS "${sdl2_image_config_path}")
    message(WARNING "${sdl2_image_config_path} does not exist: MinGW development package is corrupted")
    set(PACKAGE_VERSION_UNSUITABLE TRUE)
    return()
endif()

include("${sdl2_image_config_path}")
