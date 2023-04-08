cmake_minimum_required(VERSION 3.18)
project(microservice)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(userver)
add_subdirectory(src)
