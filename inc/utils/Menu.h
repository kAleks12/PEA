//
// Created by kacpe on 02.11.2022.
//

#pragma once

#include "../containers/AdjacencyMatrix.h"
#include "../algorithms/Algorithm.h"
#include "Enums.h"

class Menu {
private:
    static AdjacencyMatrix* graph;
public:
    static void initMenu();
    static void readGraph();
    static void displayGraph();
    static void runAlgorithm(Algorithms algorithm);
};