cmake_minimum_required(VERSION 3.10)
project(aoe2dat VERSION 1.0)
add_subdirectory(genieutils EXCLUDE_FROM_ALL)
include_directories(
        "genieutils/include"
        "${CMAKE_SOURCE_DIR}/tojson"
)
add_executable(aoe2dat aoe2dat.cpp tojson/tojson.cpp)
target_link_libraries(aoe2dat genieutils)
