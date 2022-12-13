//
// Created by kacpe on 01.12.2022.
//

#include "../../inc/algorithms/TabuSearch.h"
#include "../../inc/utils/RandomGenerator.h"
#include <cmath>
#include <iostream>

TabuSearch::TabuSearch(int iterationLimit, int maxCacheSize, int neighboursListSize):
    iterationLimit(iterationLimit),
    maxCacheSize(maxCacheSize),
    neighboursListSize(neighboursListSize)
    {}

Path *TabuSearch::execute(AdjacencyMatrix &graph) {
    int instanceSize = graph.getCitiesNumber();

    std::string currentPath = getInitialPath(instanceSize);
    int currentCost = calculatePathCost(graph, currentPath);

    std::string bestPath = currentPath;
    int bestCost = currentCost;

    DynamicArray<std::string> localBestCache;

    for (int iteration = 0; iteration < iterationLimit; iteration++) {
        DynamicArray<std::string> neighboursList = generateNeighbours(currentPath);
        currentPath = neighboursList.at(0);
        currentCost = calculatePathCost(graph, currentPath);

        for (int it = 1; it < neighboursList.getSize(); it++) {
            std::string candidatePath = neighboursList.at(it);

            if (localBestCache.contains(candidatePath)) {
                continue;
            }

            int candidateCost = calculatePathCost(graph, candidatePath);

            if (candidateCost < currentCost) {
                currentCost = candidateCost;
                currentPath = candidatePath;
            }
        }

        if (currentCost < bestCost) {
            bestPath = currentPath;
            bestCost = currentCost;
        }

        updateCache(currentPath, localBestCache);
    }

    DynamicArray<int> path;

    for (char i: bestPath) {
        path.addBack(i);
    }

    return new Path(path, bestCost);
}

void TabuSearch::testExecute(AdjacencyMatrix &graph) {
    int instanceSize = graph.getCitiesNumber();

    std::string currentPath = getInitialPath(instanceSize);
    int currentCost = calculatePathCost(graph, currentPath);

    std::string bestPath = currentPath;
    int bestCost = currentCost;

    DynamicArray<std::string> localBestCache;

    for (int iteration = 0; iteration < iterationLimit; iteration++) {
        DynamicArray<std::string> neighboursList = generateNeighbours(currentPath);
        currentPath = neighboursList.at(0);
        currentCost = calculatePathCost(graph, currentPath);

        for (int it = 1; it < neighboursList.getSize(); it++) {
            std::string candidatePath = neighboursList.at(it);

            if (localBestCache.contains(candidatePath)) {
                continue;
            }

            int candidateCost = calculatePathCost(graph, candidatePath);

            if (candidateCost < currentCost) {
                currentCost = candidateCost;
                currentPath = candidatePath;
            }
        }

        if (currentCost < bestCost) {
            bestPath = currentPath;
            bestCost = currentCost;
        }

        updateCache(currentPath, localBestCache);
    }
}

int TabuSearch::calculatePathCost(const AdjacencyMatrix &graph, const std::string &vertices) {
    int result = 0;
    int instanceSize = graph.getCitiesNumber();

    for (int i = 0; i < instanceSize; i++) {
        if (i == instanceSize - 1) {
            result += graph.getCost(vertices.at(i), vertices.at(0));
            continue;
        }

        result += graph.getCost(vertices.at(i), vertices.at(i + 1));
    }

    return result;
}

std::string TabuSearch::getInitialPath(int instanceSize) {
    std::string path;

    for (int i = 0; i < instanceSize; i++) {
        path += i;
    }

    for (int i = 0; i < instanceSize; i++) {
        swapRandomPair(path);
    }

    return path;
}

void TabuSearch::swapRandomPair(std::string &vertices) {
    int firstIndex = RandomGenerator::getInt(vertices.size() - 1);
    int secondIndex = RandomGenerator::getInt(vertices.size() - 1);

    swapPair(vertices, firstIndex, secondIndex);
}

void TabuSearch::swapPair(std::string &vertices, int firstIndex, int secondIndex) {
    char temp = vertices[firstIndex];
    vertices[firstIndex] = vertices[secondIndex];
    vertices[secondIndex] = temp;
}

DynamicArray<std::string> TabuSearch::generateNeighbours(std::string vertices) const {
    DynamicArray<std::string> neighboursList;

    for (int i = 0; i < neighboursListSize; i++) {
        int firstCity = 0;
        int secondCity = 0;

        while (firstCity == secondCity) {
            firstCity = RandomGenerator::getInt(1, vertices.size() - 1);
            secondCity = RandomGenerator::getInt(1, vertices.size() - 1);
        }

        if (firstCity > secondCity) {
            int tmp = firstCity;
            firstCity = secondCity;
            secondCity = tmp;
        }

        std::string neighbour = vertices;
        int index = firstCity;

        for (int i = secondCity; i >= firstCity; i--) {
            neighbour[i] = vertices[index];
            index++;
        }

        neighboursList.addFront(neighbour);
    }

    return neighboursList;
}

void TabuSearch::updateCache(const std::string &currentPath, DynamicArray<std::string> &cache) const {
    cache.addFront(currentPath);

    if (cache.getSize() > maxCacheSize) {
        cache.removeBack();
    }
}