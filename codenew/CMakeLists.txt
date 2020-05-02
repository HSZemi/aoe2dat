cmake_minimum_required(VERSION 3.10)
project(aoe2dat VERSION 1.0)
add_executable(aoe2dat aoe2dat.cpp)
include_directories(
    "${CMAKE_SOURCE_DIR}/genie"
    "${CMAKE_SOURCE_DIR}/jgenieutils"
    "${CMAKE_SOURCE_DIR}/tojson"
)
