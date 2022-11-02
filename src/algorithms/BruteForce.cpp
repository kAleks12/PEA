//
// Created by kacpe on 21.10.2022.
//
#include <algorithm>
#include "../../inc/algorithms/BruteForce.h"

void BruteForce::fillBuffer(size_t verticesNumber) {
    for(int index = 0; index < verticesNumber; ++index)
    {
        permutationBuffer.addBack(index);
    }

    optimalCost = INT32_MAX;
}

int BruteForce::calculateCost(const AdjacencyMatrix &matrix) {
    int totalCost = 0;
    auto lastIndex = permutationBuffer.getSize() - 1;

    for(int index = 0; index < lastIndex; index++) {
        totalCost += matrix.getCost(permutationBuffer[index], permutationBuffer[index + 1]);
    }

    totalCost += matrix.getCost(permutationBuffer[lastIndex], permutationBuffer[0]);

    return totalCost;
}

void BruteForce::reassignOptimalValues(int newOptimaCost) {
    optimalPath.clear();

    for(int i= 0; i < permutationBuffer.getSize(); i++) {
        optimalPath.addBack(permutationBuffer.at(i));
    }
    optimalPath.addBack(0);

    optimalCost = newOptimaCost;
}

Path* BruteForce::execute(AdjacencyMatrix &graph) {
    fillBuffer(graph.getCitiesNumber());

    do {
        auto currentCost = calculateCost(graph);

        if(currentCost < optimalCost) {
            reassignOptimalValues(currentCost);
        }
    } while (std::next_permutation(permutationBuffer.begin() + 1, permutationBuffer.end()));

    return new Path(optimalPath, optimalCost);
}

void BruteForce::testExecute(AdjacencyMatrix &graph) {
    fillBuffer(graph.getCitiesNumber());

    do {
        auto currentCost = calculateCost(graph);

        if(currentCost < optimalCost) {
            if(currentCost < optimalCost) {
                reassignOptimalValues(currentCost);
            }
        }
    } while (std::next_permutation(permutationBuffer.begin() + 1, permutationBuffer.end()));
}
