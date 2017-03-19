cmake_minimum_required(VERSION 2.8)
set(CURL_MIN_VERSION "7.28.0")

#	Setting up project
project(kandy)
 
#	set c++ flags
set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

# Vars
set(LIBRARY_OUTPUT_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/build)
 
#	set library directories
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/curlcpp)
include_directories(${CURLCPP_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/json)

#	Headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#	Sources
file(GLOB SOURCES "src/*.cpp")


add_library(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} curlcpp curl)

