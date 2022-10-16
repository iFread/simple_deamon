cmake_minimum_required(VERSION 3.5)

project (my_deamon)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O0 -g")

#add_library(${LIB_NAME} cored.cpp)
# создать библиотеку, которая может использоваться во всех бинарных файлах
add_subdirectory(deamon)
add_subdirectory(support)

include_directories("${PROJECT_SOURCE_DIR}/include") #заголовочные файлы


file(GLOB CPP1 "${PROJECT_SOURCE_DIR}/src/*.cpp")

#set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/build/bin/")
#add_executable(my_deamon my_deamon.cpp ${CPP1})
#add_executable(run_deamon make_root.cpp ${CPP1})
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build") #устанавливает путь
add_executable(service serv_deamon.cpp ${CPP1})

