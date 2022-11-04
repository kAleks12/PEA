//
// Created by kacpe on 25.10.2022.
//

#include <cstring>
#include "../../inc/algorithms/BranchAndBound.h"


void BranchAndBound::setupVariables(const AdjacencyMatrix &graph) {
    instanceSize = graph.getCitiesNumber();

    currPath = new int[graph.getCitiesNumber() + 1];
    currBound = 0;

    visited = new bool[graph.getCitiesNumber()];
    optimalPath = new int[graph.getCitiesNumber() + 1];

    memset(currPath, -1, instanceSize);
    memset(visited, false, instanceSize);
}

void BranchAndBound::resetVariables() {
    delete[] currPath;
    delete[] visited;
    delete[] optimalPath;
}

Path* BranchAndBound::execute(AdjacencyMatrix &graph) {
    setupVariables(graph);

    // We start at vertex 1 so the first vertex
    // in curr_path[] is 0
    visited[0] = true;
    currPath[0] = 0;

    // Call to TSPRec for curr_weight equal to
    // 0 and level 1
    TSPRec(graph, 0, 1);

    auto resultPath = createResultPath();
    resetVariables();

    return resultPath;
}

void BranchAndBound::testExecute(AdjacencyMatrix &graph) {
    setupVariables(graph);

    // We start at vertex 1 so the first vertex
    // in curr_path[] is 0
    visited[0] = true;
    currPath[0] = 0;

    // Call to TSPRec for curr_weight equal to
    // 0 and level 1
    TSPRec(graph, 0, 1);

    resetVariables();
}

void BranchAndBound::copyToFinal() {
    for (int i = 0; i < instanceSize; i++) {
        optimalPath[i] = currPath[i];
    }
    optimalPath[instanceSize] = currPath[0];
}

void BranchAndBound::TSPRec(AdjacencyMatrix &graph, int currWeight, int level) {
    // base case is when we have reached level N which
    // means we have covered all the nodes once
    if (level == instanceSize) {
        // check if there is an edge from last vertex in
        // path back to the first vertex
        if (graph.getCost(currPath[level - 1], currPath[0]) > 0) {
            // currRes has the total weight of the
            // solution we got
            int currRes = currWeight +
                          graph.getCost(currPath[level - 1], currPath[0]);

            // Update final result and final path if
            // current result is better.
            if (currRes < optimalCost) {
                copyToFinal();
                optimalCost = currRes;
            }
        }
        return;
    }

    // for any other level iterate for all vertices to
    // build the search space tree recursively
    for (int i = 0; i < instanceSize; i++) {
        // Consider next vertex if it is not same (diagonal
        // entry in adjacency matrix and not visited
        // already)
        if (graph.getCost(currPath[level - 1], i) > 0 && !visited[i]) {
            currWeight += graph.getCost(currPath[level - 1], i);

            // for the node that we have arrived on
            // If current lower bound < optimalCost, we need to explore
            // the node further
            if (currWeight < optimalCost) {
                currPath[level] = i;
                visited[i] = true;

                // call TSPRec for the next level
                TSPRec(graph, currWeight, level + 1);
            }

            // Else we have to prune the node by resetting
            // all changes to currWeight and curr_bound
            currWeight -= graph.getCost(currPath[level - 1], i);
//            currBound = temp;

            // Also reset the visited array
            memset(visited, false, graph.getCitiesNumber());

            for (int j = 0; j <= level - 1; j++) {
                visited[currPath[j]] = true;
            }
        }
    }
}

Path* BranchAndBound::createResultPath() {
    Path* result = new Path;
    for (int i = 0; i < instanceSize; i++) {
        result->addVertex(optimalPath[i]);
    }
    result->addVertex(optimalPath[instanceSize]);
    result->setCost(optimalCost);

    return result;
}