cmake_minimum_required(VERSION 3.12)
project(graph)

set(CMAKE_CXX_STANDARD 17)

add_executable(graph main.cpp list_graph.cpp matrix_graph.cpp arc_graph.cpp set_graph.cpp)