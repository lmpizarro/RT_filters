cmake_minimum_required(VERSION 3.0.2)

project (filters)

add_executable(main tests/main.c)
add_executable(test_dyn tests/test_dyn.c)
add_executable(test_filter tests/test_filter.c)
add_executable(test_rms tests/test_rms.c)

target_link_libraries(main filters m)
target_link_libraries(test_dyn dynamics filters m)
target_link_libraries(test_filter filters m)
target_link_libraries(test_rms rms filters m)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fPIC")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(filters  libs/filters)
add_library(utils  libs/utils)
add_library(dynamics  libs/dynamics)
add_library(rms  libs/rms)

include_directories(include)

#add_subdirectory(plugins/ladspa)
