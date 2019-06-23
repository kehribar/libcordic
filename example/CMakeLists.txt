# -----------------------------------------------------------------------------
# 
# -----------------------------------------------------------------------------

# ...
cmake_minimum_required(VERSION 3.0)
project(libcordic_test)
 
# ...
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/)

# ...
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -o3 -Wall -g")

# ...
file(GLOB SOURCES *.cpp *.c ../src/*.c)
add_executable(libcordic_test ${SOURCES})

# ...
target_link_libraries(libcordic_test m)
