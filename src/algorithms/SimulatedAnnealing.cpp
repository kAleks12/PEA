//
// Created by kacpe on 29.11.2022.
//

#include "../../inc/algorithms/SimulatedAnnealing.h"
#include "../../inc/utils/RandomGenerator.h"
#include <cmath>

SimulatedAnnealing::SimulatedAnnealing(const double heat, const double coolingRate) : heat(heat), coolingRate(coolingRate) {}

int SimulatedAnnealing::calculateCost(AdjacencyMatrix &graph, DynamicArray<int> &vertices) {
    int result = 0;
    int instanceSize = graph.getCitiesNumber() - 1;

    for (int i = 0; i < instanceSize; i++) {
        result += graph.getCost(vertices.at(i), vertices.at(i + 1));
    }
    result += graph.getCost(vertices.at(instanceSize), vertices.at(0));

    return result;
}

bool SimulatedAnnealing::makeDecision(const int difference, const double heat) {
    return RandomGenerator::getDouble(1) < exp(difference / heat);
}

void SimulatedAnnealing::fullShuffle(DynamicArray<int> &vertices) {
    for (int i = 0; i < vertices.getSize(); i++) {
        int firstIndex = RandomGenerator::getInt(vertices.getSize() - 1);
        int secondIndex = RandomGenerator::getInt(vertices.getSize() - 1);

        vertices.swap(firstIndex, secondIndex);
    }
}

void SimulatedAnnealing::quickShuffle(DynamicArray<int> &vertices) {

    int firstIndex = RandomGenerator::getInt(vertices.getSize() - 1);
    int secondIndex = RandomGenerator::getInt(vertices.getSize() - 1);

    vertices.swap(firstIndex, secondIndex);
}

Path *SimulatedAnnealing::execute(AdjacencyMatrix &matrix) {
    DynamicArray<int> vertices(0, matrix.getCitiesNumber());
    fullShuffle(vertices);

    int cost = calculateCost(matrix, vertices);
    currentCost = cost;
    currentSolution = vertices;
    bestCost = cost;
    bestSolution = vertices;
    double currHeat = heat;

    while (currHeat > 1) {
        DynamicArray<int> newVertices(vertices);
        quickShuffle(newVertices);

        int newCost = calculateCost(matrix, newVertices);
        int costDifference = cost - newCost;

        if (costDifference > 0 || makeDecision(costDifference, currHeat)) {
            cost = newCost;
            vertices = newVertices;
            currHeat *= coolingRate;

            if (newCost < currentCost) {
                currentCost = newCost;
                currentSolution = newVertices;
            }

            if(currentCost < bestCost) {
                bestCost = currentCost;
                bestSolution = currentSolution;
            }
        }
    }

    return new Path(bestSolution, bestCost);
}

void SimulatedAnnealing::testExecute(AdjacencyMatrix &matrix) {
    DynamicArray<int> vertices(0, matrix.getCitiesNumber());
    fullShuffle(vertices);

    int cost = calculateCost(matrix, vertices);
    double currHeat = heat;

    while (currHeat > 1) {
        DynamicArray<int> newVertices(vertices);
        quickShuffle(newVertices);

        int newCost = calculateCost(matrix, newVertices);
        int costDifference = cost - newCost;

        if (costDifference > 0 || makeDecision(costDifference, currHeat)) {
            cost = newCost;
            vertices = newVertices;
            currHeat *= 0.999;

            if (newCost < currentCost) {
                currentCost = newCost;
                currentSolution = newVertices;
            }

            if(currentCost < bestCost) {
                bestCost = currentCost;
                bestSolution = currentSolution;
            }
        }
    }
}