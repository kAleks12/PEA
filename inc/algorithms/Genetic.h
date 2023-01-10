#pragma once

#include "Algorithm.h"
#include "../utils/Enums.h"
#include "../containers/LiteDynamicArray.h"
#include "../../src/containers/LiteDynamicArray.tpp"

class Genetic : public Algorithm {
public:
    Path *execute(AdjacencyMatrix &matrix) override;
    void testExecute(AdjacencyMatrix &matrix) override;
    Genetic() = default;

private:
    int calculateCost(AdjacencyMatrix &matrix, LiteDynamicArray <size_t> &vertices);

    void updateBestSolution(AdjacencyMatrix &matrix,
                            LiteDynamicArray <size_t> &current, LiteDynamicArray <size_t> &candidate, size_t &stopSize);

    void generateIndexes(size_t &firstIndex, size_t &secondIndex, size_t verticesNumber);

    void mutation(LiteDynamicArray <size_t> &vertices);

    void swapMutation(LiteDynamicArray <size_t> &vertices);

    void insertMutation(LiteDynamicArray <size_t> &vertices);

    void invertMutation(LiteDynamicArray <size_t> &vertices);

    void scrambleMutation(LiteDynamicArray <size_t> &vertices);

    LiteDynamicArray <size_t> crossover(LiteDynamicArray <size_t> &firstParent, LiteDynamicArray <size_t> &secondParent);

    LiteDynamicArray <size_t> getInitialSolution(size_t verticesNumber);

    LiteDynamicArray <size_t> OXCrossover(LiteDynamicArray <size_t> &firstParent, LiteDynamicArray <size_t> &secondParent);

    void
    updatePopulation(AdjacencyMatrix &matrix, LiteDynamicArray <LiteDynamicArray<size_t>> &population, LiteDynamicArray <LiteDynamicArray<size_t>> &candidates);

    size_t partitionPopulation(LiteDynamicArray <LiteDynamicArray<size_t>> &population, LiteDynamicArray<size_t> &costs, int low, int high);

    void sortPopulation(LiteDynamicArray <LiteDynamicArray<size_t>> &population, LiteDynamicArray<size_t> &costs, int low, int high);

    MutationType mutationType = MutationType::Invert;
    CrossoverType crossoverType = CrossoverType::OX;
    float mutationRate = 0.5;
    float crossoverRate = 0.5;
    size_t stopSize = 1000;
    size_t populationSize = 200;
    size_t populationNumber = 3000;
    size_t eliteSize = 0.5 * populationSize;
    size_t alphaSize = 0.1 * populationSize;
};
    