 cmake_minimum_required(VERSION 3.5)

 project(support)

 include_directories("${PROJECT_SOURCE_DIR}/../include/")
 file(GLOB CPP1 "${PROJECT_SOURCE_DIR}../src/*.cpp")
 # создание вспомагательных утилит для демона
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/../bin")
 add_executable(d_start make_root.cpp ${CPP1})


