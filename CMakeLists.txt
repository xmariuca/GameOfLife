cmake_minimum_required(VERSION 3.4)
project(GameOfLife)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(SOURCE_FILES src/main.cpp src/GameOfLife.cpp)

include_directories(src)
include_directories(lib)

add_library(gameoflife_library ${SOURCE_FILES})

add_executable(GameOfLife src/main.cpp)
target_link_libraries(GameOfLife gameoflife_library)

add_executable(tests tests/tests.cpp)
target_link_libraries(tests gameoflife_library)


install (TARGETS GameOfLife DESTINATION ${PROJECT_SOURCE_DIR}/bin)
