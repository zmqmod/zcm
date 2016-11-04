cmake_minimum_required(VERSION 3.5)
project(zcm)
set (CMAKE_CXX_FLAGS "-std=c++11 -fpic")
include_directories(${zcm_SOURCE_DIR}/include)
include_directories(${CMAKE_PREFIX_PATH}/include)
add_subdirectory(src)
install(DIRECTORY ${zcm_SOURCE_DIR}/include/ DESTINATION include
        FILES_MATCHING PATTERN "*.hpp")
