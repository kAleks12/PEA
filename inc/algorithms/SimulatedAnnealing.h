//
// Created by kacpe on 29.11.2022.
//

#pragma once

#include "Algorithm.h"

class SimulatedAnnealing : public Algorithm {
    const double heat;

    static int calculateCost(AdjacencyMatrix &graph, DynamicArray<int> &vertices);
    static bool makeDecision(int delta, double temperature);
    static void fullShuffle(DynamicArray<int> &vertices);
    static void quickShuffle(DynamicArray<int> &vertices);

public:
    explicit SimulatedAnnealing(double heat = 1000);

    Path *execute(AdjacencyMatrix &matrix) override;
    void testExecute(AdjacencyMatrix &matrix) override;
};