#include "..\..\inc\algorithms\Genetic.h"
#include "..\..\inc\utils\RandomGenerator.h"

#include <stdexcept>
#include <iostream>

Path *Genetic::execute(AdjacencyMatrix &matrix) {
    LiteDynamicArray <LiteDynamicArray<size_t>> currentPopulation;
    LiteDynamicArray<size_t> currentCosts;
    int verticesNumber = matrix.getCitiesNumber();
    stopSize = verticesNumber * 10;

    while (currentPopulation.getSize() < populationSize) {
        LiteDynamicArray<size_t> solution = this->getInitialSolution(verticesNumber);
        currentPopulation.addBack(solution);
        currentCosts.addBack(this->calculateCost(matrix, solution));
    }

    this->sortPopulation(currentPopulation, currentCosts, 0, currentCosts.getSize() - 1);
    LiteDynamicArray <size_t> bestSolution = currentPopulation[0];

    size_t currentStopSize = 0;
    for (int i = 0; i < populationNumber; i++) {
        LiteDynamicArray <LiteDynamicArray<size_t>> newPopulation;
        LiteDynamicArray<size_t> newCosts;

        for (int i = 0; i < alphaSize; i++) {
            newPopulation.addBack(currentPopulation[i]);
            newCosts.addBack(this->calculateCost(matrix, currentPopulation[i]));
        }

        while (newPopulation.getSize() < populationSize) {

            size_t firstIndex;
            size_t secondIndex;
            this->generateIndexes(firstIndex, secondIndex, eliteSize);

            auto firstParent = currentPopulation[firstIndex];
            auto secondParent = currentPopulation[secondIndex];

            auto firstChild = this->crossover(firstParent, secondParent);
            auto secondChild = this->crossover(secondParent, firstParent);

            this->mutation(firstChild);
            this->mutation(secondChild);

            newPopulation.addBack(firstChild);
            newCosts.addBack(this->calculateCost(matrix, firstChild));
            newPopulation.addBack(secondChild);
            newCosts.addBack(this->calculateCost(matrix, secondChild));
        }

        this->sortPopulation(newPopulation, newCosts, 0, currentCosts.getSize() - 1);
        this->updateBestSolution(matrix, bestSolution, newPopulation[0], currentStopSize);

        currentPopulation = newPopulation;
        std::cout << i << ": " << this->calculateCost(matrix, bestSolution) << std::endl;

        if (currentStopSize > stopSize)
            break;
    }

    int bestCost = this->calculateCost(matrix, bestSolution);
    return new Path(bestSolution, bestCost);
}

void Genetic::testExecute(AdjacencyMatrix &matrix) {
    LiteDynamicArray <LiteDynamicArray<size_t>> currentPopulation;
    LiteDynamicArray<size_t> currentCosts;
    int verticesNumber = matrix.getCitiesNumber();
    stopSize = verticesNumber * 10;

    while (currentPopulation.getSize() < populationSize) {
        LiteDynamicArray<size_t> solution = this->getInitialSolution(verticesNumber);
        currentPopulation.addBack(solution);
        currentCosts.addBack(this->calculateCost(matrix, solution));
    }

    this->sortPopulation(currentPopulation, currentCosts, 0, currentCosts.getSize() - 1);
    LiteDynamicArray <size_t> bestSolution = currentPopulation[0];

    size_t currentStopSize = 0;
    for (int i = 0; i < populationNumber; i++) {
        LiteDynamicArray <LiteDynamicArray<size_t>> newPopulation;
        LiteDynamicArray<size_t> newCosts;

        for (int i = 0; i < alphaSize; i++) {
            newPopulation.addBack(currentPopulation[i]);
            newCosts.addBack(this->calculateCost(matrix, currentPopulation[i]));
        }

        while (newPopulation.getSize() < populationSize) {

            size_t firstIndex;
            size_t secondIndex;
            this->generateIndexes(firstIndex, secondIndex, eliteSize);

            auto firstParent = currentPopulation[firstIndex];
            auto secondParent = currentPopulation[secondIndex];

            auto firstChild = this->crossover(firstParent, secondParent);
            auto secondChild = this->crossover(secondParent, firstParent);

            this->mutation(firstChild);
            this->mutation(secondChild);

            newPopulation.addBack(firstChild);
            newCosts.addBack(this->calculateCost(matrix, firstChild));
            newPopulation.addBack(secondChild);
            newCosts.addBack(this->calculateCost(matrix, secondChild));
        }

        this->sortPopulation(newPopulation, newCosts, 0, currentCosts.getSize() - 1);
        this->updateBestSolution(matrix, bestSolution, newPopulation[0], currentStopSize);

        currentPopulation = newPopulation;
        std::cout << i << ": " << this->calculateCost(matrix, bestSolution) << std::endl;

        if (currentStopSize > stopSize)
            break;
    }

    int bestCost = this->calculateCost(matrix, bestSolution);
}

int Genetic::calculateCost(AdjacencyMatrix &graph, LiteDynamicArray <size_t> &path) {
    int result = 0;
    int iterationNumber = graph.getCitiesNumber() - 1;

    for (int i = 0; i < iterationNumber; i++) {
        result += graph.getCost(path[i], path[i + 1]);
    }
    result += graph.getCost(path[iterationNumber], path[0]);

    return result;
}

void Genetic::updateBestSolution(AdjacencyMatrix &matrix,
                                 LiteDynamicArray <size_t> &current, LiteDynamicArray <size_t> &candidate,
                                 size_t &stopSize) {
    int currentBestCost = this->calculateCost(matrix, current);
    int candidateCost = this->calculateCost(matrix, candidate);
    stopSize++;

    if (candidateCost < currentBestCost) {
        current = candidate;
        stopSize = 0;
    }
}

void Genetic::generateIndexes(size_t &firstIndex,
                              size_t &secondIndex, size_t verticesNumber) {
    do {
        firstIndex = RandomGenerator::getInt(0, verticesNumber - 2);
        secondIndex = RandomGenerator::getInt(0, verticesNumber - 1);
    } while (firstIndex >= secondIndex);
}

void Genetic::mutation(LiteDynamicArray <size_t> &vertices) {
    double value = RandomGenerator::getDouble(1);

    if (value > mutationRate)
        return;

    switch (mutationType) {
        case MutationType::Invert:
            this->invertMutation(vertices);
            break;
        case MutationType::Scramble:
            this->scrambleMutation(vertices);
            break;
        case MutationType::Swap:
            this->swapMutation(vertices);
            break;
        case MutationType::Insert:
            this->insertMutation(vertices);
            break;
        default:
            throw std::invalid_argument("Mutation type not supported");
            break;
    }
}

void Genetic::swapMutation(LiteDynamicArray <size_t> &vertices) {
    size_t firstIndex;
    size_t secondIndex;
    this->generateIndexes(firstIndex, secondIndex, vertices.getSize());

    vertices.swap(firstIndex, secondIndex);
}

void Genetic::insertMutation(LiteDynamicArray <size_t> &vertices) {
    size_t firstIndex;
    size_t secondIndex;
    this->generateIndexes(firstIndex, secondIndex, vertices.getSize());

    auto temp = vertices[secondIndex];
    vertices.remove(secondIndex);
    vertices.add(firstIndex, temp);
}

void Genetic::invertMutation(LiteDynamicArray <size_t> &vertices) {
    size_t firstIndex;
    size_t secondIndex;
    this->generateIndexes(firstIndex, secondIndex, vertices.getSize());

    while (firstIndex < secondIndex) {
        vertices.swap(firstIndex, secondIndex);
        firstIndex++;
        secondIndex--;
    }
}

void Genetic::scrambleMutation(LiteDynamicArray <size_t> &vertices) {
    size_t firstIndex;
    size_t secondIndex;
    this->generateIndexes(firstIndex, secondIndex, vertices.getSize());

    int swapNumber = secondIndex - firstIndex;

    for (int i = 0; i < swapNumber; i++) {
        auto firstSwapIndex = RandomGenerator::getInt(firstIndex, secondIndex);
        auto secondSwapIndex = RandomGenerator::getInt(firstIndex, secondIndex);

        vertices.swap(firstSwapIndex, secondSwapIndex);
    }
}

LiteDynamicArray <size_t>
Genetic::crossover(LiteDynamicArray <size_t> &firstParent, LiteDynamicArray <size_t> &secondParent) {
    double value = RandomGenerator::getDouble(1);

    if (value > crossoverRate)
        return firstParent;

    switch (crossoverType) {
        case CrossoverType::OX:
            return this->OXCrossover(firstParent, secondParent);
        default:
            throw std::invalid_argument("Crossover type not supported");
    }
}

LiteDynamicArray <size_t> Genetic::getInitialSolution(size_t verticesNumber) {
    LiteDynamicArray <size_t> vertices;
    for (int i = 0; i < verticesNumber; i++) {
        vertices.addBack(i);
    }

    size_t firstIndex;
    size_t secondIndex;
    for (int i = 0; i < verticesNumber; i++) {
        this->generateIndexes(firstIndex, secondIndex, verticesNumber);
        vertices.swap(firstIndex, secondIndex);
    }

    return vertices;
}

LiteDynamicArray <size_t> Genetic::OXCrossover(LiteDynamicArray <size_t> &firstParent,
                                               LiteDynamicArray <size_t> &secondParent) {
    LiteDynamicArray <size_t> result;
    size_t firstIndex;
    size_t secondIndex;
    this->generateIndexes(firstIndex, secondIndex, firstParent.getSize());

    for (int i = firstIndex; i < secondIndex; i++) {
        result.addBack(firstParent[i]);
    }

    for (int i = secondIndex - 1; i >= 0; i--) {
        auto vertex = secondParent[i];
        if (result.contains(vertex))
            continue;

        result.addFront(vertex);
    }

    for (int i = secondIndex; i < secondParent.getSize(); i++) {
        auto vertex = secondParent[i];
        if (result.contains(vertex))
            continue;

        result.addBack(vertex);
    }

    return result;
}

void Genetic::updatePopulation(AdjacencyMatrix &matrix,
                               LiteDynamicArray <LiteDynamicArray<size_t>> &population,
                               LiteDynamicArray <LiteDynamicArray<size_t>> &candidates) {
    LiteDynamicArray <size_t> bestCandidate = candidates[0];
    int bestCost = this->calculateCost(matrix, bestCandidate);
    LiteDynamicArray <size_t> secondBestCandidate = candidates[1];

    for (auto &candidate: candidates) {
        int cost = this->calculateCost(matrix, candidate);
        if (cost < bestCost) {
            secondBestCandidate = bestCandidate;
            bestCandidate = candidate;
            bestCost = cost;
        }
    }

    population.addBack(bestCandidate);
    population.addBack(secondBestCandidate);
}

size_t Genetic::partitionPopulation(LiteDynamicArray <LiteDynamicArray<size_t>> &population, LiteDynamicArray<size_t> &costs,
                                    int low, int high) {
    size_t pivot = costs[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (costs[j] < pivot) {
            i++;
            costs.swap(i, j);
            population.swap(i, j);
        }
    }

    costs.swap(i + 1, high);
    population.swap(i + 1, high);

    return i + 1;
}

void
Genetic::sortPopulation(LiteDynamicArray <LiteDynamicArray<size_t>> &population, LiteDynamicArray<size_t> &costs, int low,
                        int high) {
    if (low >= high)
        return;

    size_t pivot = this->partitionPopulation(population, costs, low, high);

    this->sortPopulation(population, costs, low, pivot - 1);
    this->sortPopulation(population, costs, pivot + 1, high);
}