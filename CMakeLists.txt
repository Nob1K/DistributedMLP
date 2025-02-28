
# Modified from thrift tutorial

## TO BUILD:
## Create a /build directory - mkdir build
## cd into build - cd build
## call cmake - cmake ..
## call make - make

cmake_minimum_required(VERSION 3.28)
project(DistributedMLP)

# Make sure gen-cpp files can be included
include_directories("${CMAKE_CURRENT_BINARY_DIR}")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/gen-cpp")

# CHANGEME set thrift include
# Use $ENV{HOME} to start the filepath from your home directory
# include the directory /thrift-0.19.0/lib/cpp/src
include_directories("$ENV{HOME}/5105/thrift-0.19.0/lib/cpp/src")

# need to include each individual cpp file from the gen-cpp folder
set(exgencpp_SOURCES
    gen-cpp/data_types.cpp
    gen-cpp/Compute.cpp
    ML.cpp
    gen-cpp/coordinator.cpp
)
add_library(exgencpp STATIC ${exgencpp_SOURCES})

# Compile compute_node executable
add_executable(compute_node compute_server.cpp)
target_link_libraries(compute_node exgencpp)

# Compile coordinator executable
add_executable(coordinator coordinator.cpp)
target_link_libraries(coordinator exgencpp)

# CHANGEME set thrift library location, link to `libthrift.so` or `libthrift.a`
# The library can be found at your thrift install location: /thrift-0.19.0/lib/cpp/.libs/libthrift.so
target_link_libraries(compute_node "$ENV{HOME}/5105/thrift-0.19.0/lib/cpp/.libs/libthrift.so")
target_link_libraries(coordinator "$ENV{HOME}/5105/thrift-0.19.0/lib/cpp/.libs/libthrift.so")

# Specify client source files
set(client_SOURCES
    client.cpp
)
# Add the client executable
add_executable(client ${client_SOURCES})
target_link_libraries(client exgencpp)
target_link_libraries(client "$ENV{HOME}/5105/thrift-0.19.0/lib/cpp/.libs/libthrift.so")


# the lines below this line were used to test compute nodes, and are not necessary for the system.
# Specify client source files
set(client_SOURCES
    compute_client.cpp
)
# Add the client executable
add_executable(compute_client ${client_SOURCES})
# Link the client with the necessary libraries (same ones as the server)
target_link_libraries(compute_client exgencpp)
# Link the thrift library for the client
target_link_libraries(compute_client "$ENV{HOME}/5105/thrift-0.19.0/lib/cpp/.libs/libthrift.so")