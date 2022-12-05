//
// Created by kacpe on 01.12.2022.
//

#pragma once

#include "Algorithm.h"

class TabuSearch : public Algorithm {
    const int iterations;
    const int recentCacheSize;
    const int plbCacheSize;

    static void updateCache(DynamicArray<std::string> &cache,
                            const std::string &newElement, int maxSize);
    static int calculateCost(AdjacencyMatrix &graph, DynamicArray<int> &path);
    static int calculateCost(AdjacencyMatrix &graph, std::string &path);
    static void fullShuffle(DynamicArray<int> &path);
    static void quickShuffle(DynamicArray<int> &path);
    static DynamicArray<int> toIntArray(const std::string& serializedData);
    static DynamicArray<std::string> generateNeighbours(DynamicArray<int> path);
    static std::string extractBest(AdjacencyMatrix &graph, DynamicArray<std::string> &path);

public:
    explicit TabuSearch(
            int recentCacheSize = 5,
            int plbCacheSize = 5,
            int iterations = 1000
    );

    Path *execute(AdjacencyMatrix &matrix) override;
    void testExecute(AdjacencyMatrix &matrix) override;
};