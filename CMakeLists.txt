
cmake_minimum_required(VERSION 2.6)


# Project settings

project(BitRPG)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Modules" ${CMAKE_MODULE_PATH})


add_subdirectory(src)
