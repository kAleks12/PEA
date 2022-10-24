cmake_minimum_required(VERSION 3.23)
project(pea)

set(CMAKE_CXX_STANDARD 23)

add_executable(
        pea src/main.cpp

        inc/containers/AdjacencyMatrix.h
        src/containers/AdjacencyMatrix.cpp

        inc/containers/DynamicArray.hpp
        src/containers/DynamicArray.tpp

        inc/algorithms/Algorithm.h

        inc/utils/Timer.h

        inc/containers/DynamicArray.hpp
        src/containers/DynamicArray.tpp

        inc/containers/Path.h
        src/containers/Path.cpp
        src/utils/Timer.cpp

        inc/algorithms/BruteForce.h
        src/algorithms/BruteForce.cpp

        inc/utils/TimeUnit.h inc/utils/FileManager.h src/utils/FileManager.cpp)
