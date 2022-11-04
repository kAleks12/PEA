//
// Created by kacper on 03.11.2022.
//

#pragma once

#include <cstdio>
#include "../../containers/AdjacencyMatrix.h"

class MatrixGenerator {
public:
    //Class variables
    static AdjacencyMatrix* graph;

    static void createGraph(int instanceSize, int costRange); //generates and assigns new AdjacencyMatrix to graph member
};