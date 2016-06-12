cmake_minimum_required(VERSION 3.0.2)

project (filters)

add_executable(main tests/main.c)

target_link_libraries(main filters m)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fPIC")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(filters  libs/filters)

include_directories(include)

#add_subdirectory(plugins/ladspa)
