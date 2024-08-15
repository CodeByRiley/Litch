cmake_minimum_required(VERSION 3.16)
project(Litch)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-fpermissive -Wdelete-incomplete -Wpointer-arith -Wno-unknown-pragmas -O0")
set(GRAPHICS "GRAPHICS_API_OPENGL_43")

set(CMAKE_BUILD_PARALLEL_LEVEL 12)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

include(FetchContent)

if (MSVC)
    # Add the compiler flag to disable exceptions globally
    add_compile_options(/EHsc-)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# Configure Assimp
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE) # Make sure zlib is enabled if you're linking against libzstd_static
set(ASSIMP_BUILD_NO_EXCEPTIONS ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_OBJ_EXPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_MTL_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_MTL_EXPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_GLTF_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_GLTF_EXPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_GLTFB_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_GLTFB_EXPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
option(ASSIMP_BUILD_STATIC_LIB "If the library shall be built as static library." ON)
set(ASSIMP_BUILD_ZLIB "1" CACHE STRING "If zlib is used, static linking. Specify Zlib < 1.3")
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
FetchContent_Declare(raylib GIT_REPOSITORY https://github.com/raysan5/raylib.git GIT_TAG 5.0)
set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "" FORCE)
FetchContent_Declare(box2d GIT_REPOSITORY https://github.com/erincatto/box2d.git GIT_TAG main)
FetchContent_MakeAvailable(raylib)
FetchContent_MakeAvailable(box2d)

add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/stb_image)
add_subdirectory(thirdparty/stb_truetype)
add_subdirectory(thirdparty/gl2d)
add_subdirectory(thirdparty/raudio)
add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/imgui-docking)
add_subdirectory(thirdparty/enet-1.3.17)
add_subdirectory(thirdparty/glui)
add_subdirectory(thirdparty/magic_enum-0.9.3)
add_subdirectory(thirdparty/safeSave)
add_subdirectory(thirdparty/profilerLib)
add_subdirectory(thirdparty/zstd-1.5.5/build/cmake)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/")
set(PROJECT_THIRDPARTY "${CMAKE_CURRENT_LIST_DIR}/thirdparty/")
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES} ${PROJECT_THIRDPARTY})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE} "${PROJECT_THIRDPARTY}/")

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
#target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/") # Uncomment this line to setup the ASSETS_PATH macro to the final assets directory when you share the game

target_link_directories(${PROJECT_NAME} PRIVATE "${PROJECT_THIRDPARTY}/")
#target_link_libraries(${PROJECT_NAME} raylib box2d glm glad stb_image stb_truetype gl2d imgui fastNoiseSIMD FastNoise2 enet glui magic_enum safeSave profilerLib
#        libzstd_static assimp)

target_link_libraries(${PROJECT_NAME} raylib box2d glm glad stb_image stb_truetype
        gl2d raudio imgui enet glui magic_enum safeSave profilerLib
        libzstd_static imm32 -static)
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
