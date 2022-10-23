 cmake_minimum_required(VERSION 3.5)

 project(support)

 include_directories("${PROJECT_SOURCE_DIR}/../include/")
 file(GLOB CPP1 "${PROJECT_SOURCE_DIR}../src/*.cpp")
 # создание вспомагательных утилит для демона
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/../bin")
set(bin_name "d_start")
add_executable(${bin_name} make_root.cpp ${CPP1})
add_custom_target(path)
add_custom_command(TARGET "path" POST_BUILD COMMAND ${CMAKE_COMMAND} -E touch "${PROJECT_SOURCE_DIR}/../bin/path.txt"
    COMMAND ${CMAKE_COMMAND} -E echo  ${PROJECT_SOURCE_DIR}/../bin/${bin_name} >> "${PROJECT_SOURCE_DIR}/../bin/path.txt")

