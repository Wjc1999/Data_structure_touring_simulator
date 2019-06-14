cmake_minimum_required (VERSION 3.10.2)

project (Touring_Simulaor)

aux_source_directory(../src/headers HEADERS)

add_compile_options(-std=c++11 -g -Og -Wall)
message(STATUS "optional: -std=c++11 -g -Wall")

add_executable(Touring_Simulaor ${HEADERS} ./main_test.cc)