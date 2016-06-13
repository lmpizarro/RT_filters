cmake_minimum_required(VERSION 3.0.2)

project (filters)

add_executable(main main.c)
add_executable(test_dyn test_dyn.c)
add_executable(test_filter test_filter.c)
add_executable(test_rms test_rms.c)

target_link_libraries(main filters m)
target_link_libraries(test_dyn dynamics filters m)
target_link_libraries(test_filter filters m)
target_link_libraries(test_rms rms filters m)

include_directories(../include)

