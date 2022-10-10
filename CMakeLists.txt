cmake_minimum_required(VERSION 3.0)

project (my_deamon)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O0 -g")


include_directories("${PROJECT_SOURCE_DIR}/include") #заголовочные файлы


file(GLOB CPP1 "${PROJECT_SOURCE_DIR}/source/*.cpp")

set(LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
add_executable(my_deamon my_deamon.cpp ${CPP1})
add_executable(run_deamon make_root.cpp ${CPP1})
set(LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")
add_executable(service serv_deamon.cpp ${CPP1})

