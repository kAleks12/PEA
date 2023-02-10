#pragma once

#include "Algorithm.h"
#include "../utils/Enums.h"
#include "../../inc/algorithms/utils/GeneticHelper.h"

class Genetic : public Algorithm {
public:
    Path *execute(AdjacencyMatrix &graph) override;
    void testExecute(AdjacencyMatrix &matrix) override;
    Genetic() = default;

    void setMutationType(MutationType mutationType);

    void setCrossoverType(CrossoverType crossoverType);

    void setMutationRate(float mutationRate);

    void setCrossoverRate(float crossoverRate);

    void setStopSize(size_t stopSize);

    void setPopulationSize(size_t populationSize);

    void setPopulationNumber(size_t populationNumber);

    void setEliteSize(float eliteSize);

    void setAlphaSize(float alphaSize);

private:
    void mutate(LiteDynamicArray <size_t> &path);

    LiteDynamicArray <size_t> crossover(LiteDynamicArray <size_t> &firstParent, LiteDynamicArray <size_t> &secondParent);

    static LiteDynamicArray <size_t> getInitialSolution(size_t verticesNumber);

    static size_t partitionPopulation(LiteDynamicArray <Member> &population, int low, int high);

    void sortPopulation(LiteDynamicArray <Member> &population, int low, int high);

    MutationType mutationType = MutationType::Invert;
    CrossoverType crossoverType = CrossoverType::OX;
    float mutationRate = 0.5;
    float crossoverRate = 0.5;
    size_t stopSize = 1000;
    size_t populationSize = 300;
    size_t populationNumber = 3000;
    int eliteSize = 0.5 * populationSize;
    int alphaSize = 0.1 * populationSize;
};
