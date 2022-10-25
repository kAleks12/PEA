//
// Created by kacpe on 25.10.2022.
//

#pragma once

#include "Algorithm.h"

class BandB : public Algorithm {
private:
    size_t instanceSize{};

    int* currPath{};
    int currBound{};
    bool* visited{};

    int* optimalPath{};
    int optimalCost = INT_MAX;

    static int firstMin(AdjacencyMatrix &graph, int vertex);
    static int secondMin(AdjacencyMatrix &graph, int vertex);

    void setupVariables(const AdjacencyMatrix &graph);
    void copyToFinal();
    void TSPRec(AdjacencyMatrix &graph, int currWeight, int level);
    Path* createResultPath();

public:
    Path* execute(AdjacencyMatrix &graph, int initialVertex) override;
    void testExecute(AdjacencyMatrix &graph, int initialVertex) override;
};