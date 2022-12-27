#pragma once

#include "Algorithm.h"
#include "../containers/Member.h"
#include "../../inc/containers/LiteDynamicArray.h"
#include "../../src/containers/LiteDynamicArray.tpp"
#include "../utils/Enums.h"


#include <vector>
#include <algorithm>

class Genetic : public Algorithm {
    double mutationProbability = 1;
    double crossoverProbability = 1;
    size_t populationSize = 400; //TODO swap for ratio based on instance size
    MutationType mutationType = MutationType::Insert;
    int iterationNumber = 10000;
    int xxx = 0.25 * iterationNumber; //TODO change name


    DynamicArray<int> swapRandomPair(const DynamicArray<int> &buffer);
    void swapPair(DynamicArray<int> &buffer, int first, int second);
    int calculatePathCost(const AdjacencyMatrix &graph, const DynamicArray<int> &path);

    void generateFirstPopulation(const AdjacencyMatrix &graph, LiteDynamicArray<Member> &emptyPopulation);
    void crossover(LiteDynamicArray<Member> &oldPopulation, LiteDynamicArray<Member> &newPopulation,
                   const AdjacencyMatrix &graph);
    void mutate(LiteDynamicArray<Member> &newPopulation);
    DynamicArray<int> performPMX(DynamicArray<int> &firstParent, DynamicArray<int> &secondParent);
    DynamicArray<int> calcMember(const DynamicArray<int> &startBuffer);

public:
    Genetic() = default;
    Genetic(double mutationProbability, double crossoverProbability, size_t populationSize,
            MutationType mutationType, int iterationNumber, int xxx) :
            mutationProbability(mutationProbability), crossoverProbability(crossoverProbability),
            populationSize(populationSize), mutationType(mutationType),
            iterationNumber(iterationNumber), xxx(xxx) {}

    void setIterationNumber(int newNumber) {
        iterationNumber = newNumber;
    }
    void setPopulationSize(size_t newSize) {
        populationSize = newSize;
    }
    void setMutationType(MutationType newType) {
        mutationType = newType;
    }
    void setMutationProbability(double newProbability) {
        mutationProbability = newProbability;
    }
    void setCrossoverProbability(double newProbability) {
        crossoverProbability = newProbability;
    }

    Path *execute(AdjacencyMatrix &graph) override;
    void testExecute(AdjacencyMatrix &graph) override;
};
