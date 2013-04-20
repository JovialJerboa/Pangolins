cmake_minimum_required (VERSION 2.6)
project (Pangolins)

# add the binary tree to the search path for include files
# so that we will find Pangolins.h
include_directories("${PROJECT_BINARY_DIR}")

# add the executable
add_executable(Pangolins pangolins.cpp)