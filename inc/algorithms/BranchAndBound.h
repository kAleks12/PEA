//
// Created by kacpe on 25.10.2022.
//

#pragma once

#include "Algorithm.h"

class BranchAndBound : public Algorithm {
private:
    size_t instanceSize{};

    int* currPath{};
    int currBound{};
    bool* visited{};

    int* optimalPath{};
    int optimalCost = INT_MAX;

    void setupVariables(const AdjacencyMatrix &graph);
    void resetVariables();
    void copyToFinal();
    void TSPRec(AdjacencyMatrix &graph, int currWeight, int level);
    Path* createResultPath();

public:
    Path* execute(AdjacencyMatrix &graph) override;
    void testExecute(AdjacencyMatrix &graph) override;
};