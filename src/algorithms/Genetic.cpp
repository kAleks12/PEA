#include "..\..\inc\algorithms\Genetic.h"
#include "..\..\inc\utils\RandomGenerator.h"

#include <stdexcept>
#include <iostream>

Path *Genetic::execute(AdjacencyMatrix &graph) {
    LiteDynamicArray<Member> currentPopulation;
    int verticesNumber = graph.getCitiesNumber();
    stopSize = verticesNumber * 10;

    while (currentPopulation.getSize() < populationSize) {
        LiteDynamicArray<size_t> solution = getInitialSolution(verticesNumber);
        Member newMember(solution, graph.getPathCost(solution));
        currentPopulation.addBack(newMember);
    }

    sortPopulation(currentPopulation, 0, currentPopulation.getSize() - 1);
    Member bestSolution = currentPopulation[0];
    size_t currentStopSize = 0;

    for (int i = 0; i < populationNumber; i++) {
        LiteDynamicArray<Member> newPopulation;

        for (int j = 0; j < alphaSize; j++) {
            newPopulation.addBack(currentPopulation[j]);
        }

        while (newPopulation.getSize() < populationSize) {
            size_t firstIndex;
            size_t secondIndex;
            RandomGenerator::generatePair(firstIndex, secondIndex, eliteSize);

            Member firstParent = currentPopulation[firstIndex];
            Member secondParent = currentPopulation[secondIndex];

            LiteDynamicArray<size_t> firstChild = crossover(firstParent.path, secondParent.path);
            LiteDynamicArray<size_t> secondChild = crossover(secondParent.path, firstParent.path);

            mutate(firstChild);
            mutate(secondChild);

            Member firstMember(firstChild, graph.getPathCost(firstChild));
            Member secondMember(secondChild, graph.getPathCost(secondChild));

            newPopulation.addBack(firstMember);
            newPopulation.addBack(secondMember);
        }

        sortPopulation(newPopulation, 0, currentPopulation.getSize() - 1);
        Member candidate = newPopulation.at(0);

        if( candidate.cost < bestSolution.cost) {
            stopSize = 0;
            bestSolution = candidate;
        }

        currentPopulation = newPopulation;

        if (currentStopSize > stopSize) {
            break;
        }
    }

    return new Path(bestSolution.path, bestSolution.cost);
}

void Genetic::testExecute(AdjacencyMatrix &matrix) {
}

void Genetic::mutate(LiteDynamicArray<size_t> &vertices) {
    double shouldMutate = RandomGenerator::getDouble(1);

    if (shouldMutate > mutationRate) {
        return;
    }

    switch (mutationType) {
        case MutationType::Invert:
            GeneticHelper::invertMutation(vertices);
            break;

        case MutationType::Scramble:
            GeneticHelper::scrambleMutation(vertices);
            break;

        case MutationType::Swap:
            GeneticHelper::swapMutation(vertices);
            break;

        case MutationType::Insert:
            GeneticHelper::insertMutation(vertices);
            break;

        default:
            throw std::invalid_argument("Mutation type not supported");
    }
}

LiteDynamicArray<size_t>
Genetic::crossover(LiteDynamicArray<size_t> &firstParent, LiteDynamicArray<size_t> &secondParent) {
    double value = RandomGenerator::getDouble(1);

    if (value > crossoverRate) {
        return firstParent;
    }

    switch (crossoverType) {
        case CrossoverType::OX:
            return GeneticHelper::OXCrossover(firstParent, secondParent);
        default:
            throw std::invalid_argument("Crossover type not supported");
    }
}

LiteDynamicArray<size_t> Genetic::getInitialSolution(size_t verticesNumber) {
    LiteDynamicArray<size_t> vertices;
    for (int i = 0; i < verticesNumber; i++) {
        vertices.addBack(i);
    }

    size_t firstIndex;
    size_t secondIndex;
    for (int i = 0; i < verticesNumber; i++) {
        RandomGenerator::generatePair(firstIndex, secondIndex, verticesNumber);
        vertices.swap(firstIndex, secondIndex);
    }

    return vertices;
}

size_t Genetic::partitionPopulation(LiteDynamicArray<Member> &population, int low, int high) {
    size_t pivot = population[high].cost;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (population[j].cost < pivot) {
            i++;
            population.swap(i, j);
        }
    }

    population.swap(i + 1, high);

    return i + 1;
}

void Genetic::sortPopulation(LiteDynamicArray<Member> &population, int low, int high) {
    if (low >= high) {
        return;
    }

    size_t pivot = this->partitionPopulation(population, low, high);

    this->sortPopulation(population, low, pivot - 1);
    this->sortPopulation(population, pivot + 1, high);
}

void Genetic::setMutationType(MutationType newType) {
    this->mutationType = newType;
}

void Genetic::setCrossoverType(CrossoverType newType) {
    this->crossoverType = newType;
}

void Genetic::setMutationRate(float newType) {
    this->mutationRate = newType;
}

void Genetic::setCrossoverRate(float newType) {
    this->crossoverRate = newType;
}

void Genetic::setStopSize(size_t newSize) {
    this->stopSize = newSize;
}

void Genetic::setPopulationSize(size_t newSize) {
    this->populationSize = newSize;
    this->alphaSize = populationSize*0.1;
    this->eliteSize = populationSize*0.5;
}

void Genetic::setPopulationNumber(size_t newNumber) {
    this->populationNumber = newNumber;
}

void Genetic::setEliteSize(size_t newSize) {
    this->eliteSize = newSize;
}

void Genetic::setAlphaSize(size_t newSize) {
    this->alphaSize = newSize;
}
