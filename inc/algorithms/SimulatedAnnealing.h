//
// Created by kacpe on 29.11.2022.
//

#pragma once

#include "Algorithm.h"

class SimulatedAnnealing : public Algorithm {
    const double heat;
    const double coolingRate;
    DynamicArray<int> currentSolution;
    int currentCost;
    int bestCost;
    DynamicArray<int> bestSolution;

    static int calculateCost(AdjacencyMatrix &graph, DynamicArray<int> &vertices);
    static bool makeDecision(int delta, double temperature);
    static void fullShuffle(DynamicArray<int> &vertices);
    static void quickShuffle(DynamicArray<int> &vertices);

public:
    explicit SimulatedAnnealing(double heat = 1000, double coolingRate = 0.999);

    Path *execute(AdjacencyMatrix &matrix) override;
    void testExecute(AdjacencyMatrix &matrix) override;
};