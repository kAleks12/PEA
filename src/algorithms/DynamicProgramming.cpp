//
// Created by kacpe on 31.10.2022.
//

#include "../../inc/algorithms/DynamicProgramming.h"
#include <cmath>

Path *DynamicProgramming::execute(AdjacencyMatrix &graph) {

    setupVariables(graph);
    Result result = TSP(graph, 0, 1);

    auto path = createResultPath();
    resetState();

    return path;
}

void DynamicProgramming::testExecute(AdjacencyMatrix &graph) {
    setupVariables(graph);
    Result result = TSP(graph, 0, 1);
    resetState();
}

void DynamicProgramming::setupVariables(const AdjacencyMatrix &graph) {
    instanceSize = graph.getCitiesNumber();
    numOfPaths = int (pow(2, instanceSize) - 1);

    state = new Result *[instanceSize];
    for (int i = 0; i < instanceSize; i++) {
        state[i] = new Result[numOfPaths];
    }
}



Result DynamicProgramming::TSP(AdjacencyMatrix &graph, int currVertex, int visitedMask) {
    if (visitedMask == numOfPaths) {
        return Result(graph.getCost(currVertex, 0), currVertex); // return to starting city
    }

    if (state[currVertex][visitedMask].cost != INT_MAX)
        return state[currVertex][visitedMask];

    for (int i = 0; i < instanceSize; ++i) {
        // can't visit ourselves unless we're ending & skip if already visited
        if (i == currVertex || (visitedMask & (1 << i)))
            continue;

        auto result = TSP(graph, i, visitedMask | (1 << i));
        result.cost += graph.getCost(currVertex, i);
        result.path.addFront(currVertex);

        if (result.cost < state[currVertex][visitedMask].cost) {
            state[currVertex][visitedMask].path.clear();
            state[currVertex][visitedMask].cost = result.cost;

            for (int i = 0; i < result.path.getSize(); i++) {
                state[currVertex][visitedMask].path.addBack(result.path[i]);
            }
        }
    }

    return state[currVertex][visitedMask];
}

Path *DynamicProgramming::createResultPath() {
    Path* result = new Path;

    for (int i = 0; i < instanceSize; i++) {
        result->addVertex(state[0][1].path.at(i));
    }
    result->addVertex(0);
    result->setCost(state[0][1].cost);

    return result;
}

void DynamicProgramming::resetState() {
    for (int i = 0; i < instanceSize; i++) {
        delete[] state[i];
    }
    delete[] state;
}
