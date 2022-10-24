//
// Created by kacpe on 21.10.2022.
//
#include <algorithm>
#include "../../inc/algorithms/BruteForce.h"

void BruteForce::fillBuffer(size_t verticesNumber, size_t initialVertex) {
    for(int index = 0; index < verticesNumber; ++index)
    {
        permutationBuffer.addBack(index);
    }
}

int BruteForce::calculateCost(const AdjacencyMatrix &matrix) {
    int totalCost = 0;

    for(int index = 0; index < permutationBuffer.getSize() - 1; index++) {
        totalCost += matrix.getCost(permutationBuffer[index], permutationBuffer[index + 1]);
    }

    return totalCost;
}

Path BruteForce::execute(const AdjacencyMatrix &graph, int initialVertex) {
    testExecute(graph, initialVertex);

    return optimalPath;
}

void BruteForce::testExecute(const AdjacencyMatrix &graph, int initialVertex) {
    fillBuffer(graph.getCitiesNumber(), 0);

    do {
        auto currentCost = calculateCost(graph);

        if(currentCost < optimalPath.getCost()) {
            optimalPath = Path(permutationBuffer, currentCost);
        }
    } while (std::next_permutation(permutationBuffer.begin(), permutationBuffer.end()));
}
