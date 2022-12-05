//
// Created by kacpe on 01.12.2022.
//

#include "../../inc/algorithms/TabuSearch.h"
#include "../../inc/utils/RandomGenerator.h"
#include <cmath>

TabuSearch::TabuSearch(const int recentCacheSize, const int plbCacheSize, const int iterations) :
        iterations(iterations), recentCacheSize(recentCacheSize), plbCacheSize(plbCacheSize) {}

int TabuSearch::calculateCost(AdjacencyMatrix &graph, DynamicArray<int> &vertices) {
    int result = 0;
    int instanceSize = graph.getCitiesNumber() - 1;

    for (int i = 0; i < instanceSize; i++) {
        result += graph.getCost(vertices.at(i), vertices.at(i + 1));
    }
    result += graph.getCost(vertices.at(instanceSize), vertices.at(0));

    return result;
}

int TabuSearch::calculateCost(AdjacencyMatrix &graph, std::string &vertices) {
    int result = 0;
    int instanceSize = graph.getCitiesNumber() - 1;

    for (int i = 0; i < instanceSize; i++) {
        result += graph.getCost(vertices.at(i), vertices.at(i + 1));
    }
    result += graph.getCost(vertices.at(instanceSize), vertices.at(0));

    return result;
}

void TabuSearch::fullShuffle(DynamicArray<int> &path) {
    for (int i = 0; i < path.getSize(); i++) {
        quickShuffle(path);
    }
}

void TabuSearch::quickShuffle(DynamicArray<int> &path) {

    int firstIndex = RandomGenerator::getInt(path.getSize() - 1);
    int secondIndex = RandomGenerator::getInt(path.getSize() - 1);

    path.swap(firstIndex, secondIndex);
}

DynamicArray<int> TabuSearch::toIntArray(const std::string& serializedData) {
    DynamicArray<int> output;

    for (char c: serializedData) {
        output.addBack(c);
    }

    return output;
}

DynamicArray<std::string> TabuSearch::generateNeighbours(DynamicArray<int> path) {
    DynamicArray<std::string> neighbours;

    for (int i = 0; i < path.getSize() - 1; i++) {
        path.swap(i, i + 1);
        neighbours.addBack(path.serialize());
        path.swap(i, i + 1);
    }

    path.swap(path.getSize() - 1, 0);
    neighbours.addBack(path.serialize());

    return neighbours;
}

std::string TabuSearch::extractBest(AdjacencyMatrix &graph, DynamicArray<std::string>& path) {
    std::string bestSolution = path.at(0);
    int bestCost = calculateCost(graph, bestSolution);
    int index = 0;

    for (int i = 1; i < path.getSize(); ++i) {
        int cost = calculateCost(graph, path[i]);
        if (cost < bestCost)
        {
            bestSolution = path[i];
            bestCost = cost;
            index = i;
        }
    }

    path.remove(index);

    return bestSolution;
}

void TabuSearch::updateCache(DynamicArray<std::string> &cache, const std::string &newElement, int maxSize) {
    cache.addFront(newElement);

    if (cache.getSize() > maxSize) {
        cache.removeBack();
    }
}

Path *TabuSearch::execute(AdjacencyMatrix &matrix) {
    DynamicArray<std::string> recentCache;
    DynamicArray<std::string> previousBestCache;

    DynamicArray<int> bestSolution(0, matrix.getCitiesNumber());
    fullShuffle(bestSolution);
    int bestCost = calculateCost(matrix, bestSolution);
    std::string serializedBestSolution = bestSolution.serialize();

    for (int currIteration = 0; currIteration < iterations; ++currIteration) {
        DynamicArray<std::string> neighbours = generateNeighbours(bestSolution);

        while(!neighbours.isEmpty()) {
            std::string bestCandidate = extractBest(matrix, neighbours);

            if (previousBestCache.contains(bestCandidate) || recentCache.contains(bestCandidate)) {
                continue;
            }

            int neighbourCost = calculateCost(matrix, bestCandidate);

            if (neighbourCost < bestCost) {
                updateCache(previousBestCache, serializedBestSolution, plbCacheSize);
                bestCost = neighbourCost;
                bestSolution = toIntArray(bestCandidate);
                serializedBestSolution = bestCandidate;
                break;
            }

            updateCache(recentCache, bestCandidate, recentCacheSize);
        }
    }

    return new Path(bestSolution, bestCost);
}

void TabuSearch::testExecute(AdjacencyMatrix &matrix) {}