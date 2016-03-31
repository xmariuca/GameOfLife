cmake_minimum_required(VERSION 2.9)
project(GameOfLife)

#if(NOT CMAKE_BUILD_TYPE)
#    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
#endif()

find_package(OpenMP)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/GameOfLife.cpp)

include_directories(src)
include_directories(lib)

add_library(gameoflife_library ${SOURCE_FILES})

add_executable(omp_GameOfLife src/main.cpp)
target_link_libraries(omp_GameOfLife gameoflife_library)

add_executable(tests tests/tests.cpp)
target_link_libraries(tests gameoflife_library)


install (TARGETS omp_GameOfLife DESTINATION ${PROJECT_SOURCE_DIR}/bin)
