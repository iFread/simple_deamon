 
cmake_minimum_required(VERSION 3.5)
project(my_deamon)

include_directories("${PROJECT_SOURCE_DIR}/../include/")
file (GLOB CPP1 "${PROJECT_SOURCE_DIR}../src/*.cpp")


add_executable(sim_deamon  my_deamon.cpp "${CPP1}")


