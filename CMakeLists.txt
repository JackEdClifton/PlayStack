cmake_minimum_required(VERSION 3.31)
project(PlayStack LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries")

set(SFML_BUILD_EXAMPLE OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_TEST_SUITE OFF CACHE BOOL "" FORCE)

add_subdirectory(sfml)

add_subdirectory(FlappyBird)

