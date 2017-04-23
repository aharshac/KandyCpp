cmake_minimum_required(VERSION 2.8)
set(CURL_MIN_VERSION "7.28.0")

#	Setting up project
project(KANDY)
 
#	set c++ flags
set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

# Vars
set(LIBRARY_OUTPUT_PATH  build)
 
#	set library directories
add_subdirectory(${KANDY_SOURCE_DIR}/lib/curlcpp)

#	include Headers
include_directories(${CURLCPP_SOURCE_DIR}/include)
include_directories(${KANDY_SOURCE_DIR}/lib/json)
include_directories(${KANDY_SOURCE_DIR}/include)

file(GLOB HEADERS "${KANDY_SOURCE_DIR}/include/*.hpp")
install (FILES ${HEADERS} DESTINATION include)

#	Sources
file(GLOB SOURCES "src/*.cpp")

add_library(kandy ${HEADERS} ${SOURCES})
target_link_libraries(kandy curlcpp curl)

install (TARGETS kandy LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

# 	macro for use in dependents 
macro(kandy_include_dependencies)
  MESSAGE(STATUS "# Kandy: Including dependencies")
  include_directories(${CURLCPP_SOURCE_DIR}/include)
  include_directories(${KANDY_SOURCE_DIR}/lib/json)
  include_directories(${KANDY_SOURCE_DIR}/include)
endmacro()

