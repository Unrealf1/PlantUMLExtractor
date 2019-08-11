cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(PlantUMLExtractor)

option(DEBUG "Build with debug flags" OFF)

if (DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fsanitize=address,undefined -g")
endif(DEBUG)

file(GLOB_RECURSE SOURCES . source/*.cpp)

add_executable(PlantUMLExtractor ${SOURCES})

target_include_directories(PlantUMLExtractor PUBLIC "./include")
