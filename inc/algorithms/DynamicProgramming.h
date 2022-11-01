//
// Created by kacpe on 31.10.2022.
//

#pragma once

#include "Algorithm.h"

struct Result {
    int cost;
    DynamicArray<int> path;

    Result(int cost, int firstVertex) {
        this->cost = cost;
        path.addBack(firstVertex);
    };

    Result() {
        this->cost = INT_MAX;
    };

};

class DynamicProgramming : public Algorithm {
private:
    size_t instanceSize{};
    size_t numOfPaths{};
    Result ** state;

    void resetState();
    void setupVariables(const AdjacencyMatrix &graph);
    Result TSP(AdjacencyMatrix &graph, int currVertex, int visitedMask);
    Path* createResultPath();

public:
    Path* execute(AdjacencyMatrix &graph, int initialVertex) override;
    void testExecute(AdjacencyMatrix &graph, int initialVertex) override;
};


