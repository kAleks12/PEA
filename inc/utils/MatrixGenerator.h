//
// Created by kacpe on 03.11.2022.
//

#pragma once

#include <cstdio>
#include "../containers/AdjacencyMatrix.h"

class MatrixGenerator {
public:
    static AdjacencyMatrix* graph;

    static void createGraph(int instanceSize);
};