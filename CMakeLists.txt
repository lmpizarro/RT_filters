cmake_minimum_required(VERSION 3.0.2)

project (filters)

add_executable(main tests/main.c)

target_link_libraries(main filters m)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fPIC")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(filters  libs/filters)
add_library(utils  libs/utils)
add_library(dynamics  libs/dynamics)
add_library(rms  libs/rms)

include_directories(include)

#add_subdirectory(plugins/ladspa)
