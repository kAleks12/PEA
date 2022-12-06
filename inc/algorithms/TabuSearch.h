//
// Created by kacpe on 01.12.2022.
//

#pragma once

#include "Algorithm.h"

class TabuSearch : public Algorithm {
    const int iterationLimit;
    const int maxCacheSize;
    const int neighboursListSize;

    static int calculatePathCost(const AdjacencyMatrix &graph, const std::string &vertices);
    static std::string getInitialPath(int instanceSize);
    static void swapRandomPair(std::string &vertices);
    static void swapPair(std::string &vertices, int firstIndex, int secondIndex);

    DynamicArray<std::string> generateNeighbours(std::string vertices) const;
    void updateCache(const std::string &currentPath, DynamicArray<std::string> &cache) const;

public:
    explicit TabuSearch(
            int iterationLimit = 3000,
            int maxCacheSize = 200,
            int neighboursListSize = 100
                    );

    void testExecute(AdjacencyMatrix &graph) override;

    Path *execute(AdjacencyMatrix &graph) override;
};