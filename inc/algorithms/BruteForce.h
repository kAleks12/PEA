//
// Created by kacpe on 21.10.2022.
//

#pragma once

#include "Algorithm.h"

class BruteForce : public Algorithm {
private:
    DynamicArray<int> permutationBuffer;
    DynamicArray<int>* optimalPath = nullptr;
    int optimalCost;

    void fillBuffer(size_t verticesNumber);
    int calculateCost(const AdjacencyMatrix &matrix);
    void reassignOptimalValues(int newOptimaCost);

public:
    Path* execute(AdjacencyMatrix &graph, int initialVertex) override;
    void testExecute(AdjacencyMatrix &graph, int initialVertex) override;
};
