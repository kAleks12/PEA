cmake_minimum_required(VERSION 3.23)
project(pea)

set(CMAKE_CXX_STANDARD 23)

add_executable(
        pea src/main.cpp

        inc/containers/AdjacencyMatrix.h
        src/containers/AdjacencyMatrix.cpp

        inc/containers/DynamicArray.hpp
        src/containers/DynamicArray.tpp

        inc/containers/Path.h
        src/containers/Path.cpp

        inc/utils/Enums.h

        inc/utils/Menu.h
        src/utils/Menu.cpp

        inc/utils/Timer.h
        src/utils/Timer.cpp

        inc/utils/FileManager.h
        src/utils/FileManager.cpp

        inc/utils/MatrixGenerator.h
        src/utils/MatrixGenerator.cpp

        inc/algorithms/Algorithm.h

        inc/algorithms/BruteForce.h
        src/algorithms/BruteForce.cpp

        inc/algorithms/BranchAndBound.h
        src/algorithms/BranchAndBound.cpp

        inc/algorithms/DynamicProgramming.h
        src/algorithms/DynamicProgramming.cpp
)
