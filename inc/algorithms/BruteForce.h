//
// Created by kacpe on 21.10.2022.
//

#pragma once

#include "Algorithm.h"

class BruteForce : public Algorithm {
private:
    DynamicArray<int> permutationBuffer;
    Path optimalPath;

    void fillBuffer(size_t verticesNumber, size_t initialVertex);
    int calculateCost(const AdjacencyMatrix &matrix);

public:
    Path execute(const AdjacencyMatrix &graph, int initialVertex) override;
    void testExecute(const AdjacencyMatrix &graph, int initialVertex) override;
};
