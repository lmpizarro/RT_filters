cmake_minimum_required(VERSION 3.0.2)

project (filters)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fPIC")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(filters  libs/filters)
add_library(shelf_filters  libs/shelf_filters)

add_library(utils  libs/utils)
add_library(dynamics  libs/dynamics)
add_library(rms  libs/rms)

include_directories(include)

add_subdirectory(tests)
