cmake_minimum_required(VERSION 3.10)
project(ShaderClass)

set(path_to_glad "~/Programming/C++/glad/")

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
#
include_directories(${path_to_glad}/include)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-lglfw -ldl")

add_library(GLAD ${path_to_glad}/src/glad.c)

add_library(ShaderClass Src/ShaderClass/ShaderClass.cpp)

add_executable(solution Src/main.cpp)

target_link_libraries(solution GLAD ShaderClass)