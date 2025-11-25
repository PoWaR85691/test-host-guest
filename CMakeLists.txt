cmake_minimum_required(VERSION 3.20)

project(test-host-guest LANGUAGES CXX)

include_directories(lib)

add_subdirectory(lib)
add_subdirectory(guest)
add_subdirectory(host)