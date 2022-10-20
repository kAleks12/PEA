cmake_minimum_required(VERSION 3.23)
project(pea)

set(CMAKE_CXX_STANDARD 23)

add_executable(
        pea main.cpp

        inc/containers/AdjacencyMatrix.h
        src/containers/AdjacencyMatrix.cpp

        inc/containers/DynamicArray.hpp
        src/containers/DynamicArray.tpp
)
