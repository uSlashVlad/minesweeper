cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS ON)

project(MineSweeper VERSION 0.1.0)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

file(GLOB_RECURSE SRC_FILES src/*)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

## In most cases better set in the CMake cache
set(SFML_DIR "/usr/lib/cmake/SFML")
find_package(SFML 2.5 REQUIRED network audio graphics window system)
target_include_directories(${PROJECT_NAME} PUBLIC ${SFML_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-audio)
