#include "../../inc/Algorithms/Genetic.h"
#include "../../inc/utils/RandomGenerator.h"

void Genetic::generateFirstPopulation(const AdjacencyMatrix &graph, LiteDynamicArray<Member> &emptyPopulation) {
    DynamicArray<int> cities;

    for (int i = 0; i < graph.getCitiesNumber(); ++i) {
        cities.addBack(i);
    }

    for (int i = 0; i < populationSize; ++i) {
        DynamicArray<int> path = calcMember(cities);
        int cost = calculatePathCost(graph, path);

        Member newMember(path, cost);
        emptyPopulation.addBack(newMember);
    }
}

DynamicArray<int> Genetic::calcMember(const DynamicArray<int> &startBuffer) {
    DynamicArray<int> newBuffer = startBuffer;

    for (int i = 0; i < populationSize; ++i) {
        newBuffer = swapRandomPair(newBuffer);
    }

    return newBuffer;
}

DynamicArray<int> Genetic::swapRandomPair(const DynamicArray<int> &buffer) {
    DynamicArray<int> newBuffer = buffer;

    for (int i = 0; i < buffer.getSize(); ++i) {
        auto firstIndex = RandomGenerator::getInt(buffer.getSize() - 1);
        auto secondIndex = RandomGenerator::getInt(buffer.getSize() - 1);

        swapPair(newBuffer, firstIndex, secondIndex);
    }

    return newBuffer;
}

void Genetic::swapPair(DynamicArray<int> &buffer, int firstIndex, int secondIndex) {
    char temp = buffer[firstIndex];
    buffer[firstIndex] = buffer[secondIndex];
    buffer[secondIndex] = temp;
}

int Genetic::calculatePathCost(const AdjacencyMatrix &graph, const DynamicArray<int> &path) {
    int result = 0;
    int instanceSize = graph.getCitiesNumber();

    for (int i = 0; i < instanceSize; i++) {
        if (i == instanceSize - 1) {
            result += graph.getCost(path.at(i), path.at(0));
            continue;
        }

        result += graph.getCost(path.at(i), path.at(i + 1));
    }

    return result;
}

void Genetic::crossover(LiteDynamicArray<Member> &oldPopulation, LiteDynamicArray<Member> &newPopulation,
                        const AdjacencyMatrix &graph) {
    for (int i = 0; i < populationSize / 2; i++) {
        auto randomProbability = RandomGenerator::getDouble(1.0);

        if (randomProbability > crossoverProbability) {
            newPopulation.addBack(oldPopulation[i]);
            newPopulation.addBack(oldPopulation[i + 1]);
//            std::cout << "skip crossover" << std::endl;
            continue;
        }

        auto firstPath = oldPopulation[i].getPath();
        auto secondPath = oldPopulation[i + 1].getPath();

        auto firstChild = performPMX(firstPath, secondPath);
        auto secondChild = performPMX(secondPath, firstPath);

        int firstCost = calculatePathCost(graph, firstPath);
        int secondCost = calculatePathCost(graph, secondPath);

        newPopulation.addBack(Member(firstChild, firstCost));
        newPopulation.addBack(Member(secondChild, secondCost));
    }
}

void Genetic::mutate(LiteDynamicArray<Member> &newPopulation) {
    for (int i = 0; i < populationSize; ++i) {
        auto randomProbability = RandomGenerator::getDouble(1.0);

        if (randomProbability > mutationProbability) {
//            std::cout << "skip mutation" << std::endl;
            continue;
        }

        auto currMember = newPopulation[i];
        int firstIndex{0}, secondIndex{0};

        while (firstIndex >= secondIndex) {
            firstIndex = RandomGenerator::getInt(currMember.getPath().getSize() - 1);
            secondIndex = RandomGenerator::getInt(currMember.getPath().getSize() - 1);
        }

        auto path = currMember.getPath();

        switch (mutationType) {
            case MutationType::Swap:
                path.swap(firstIndex, secondIndex);

                break;

            case MutationType::Insert:
                auto temp = path[secondIndex];
                for (int i = secondIndex; i > firstIndex; --i) {
                    path[i] = path[i - 1];
                }
                path[firstIndex] = temp;

                break;
        }
        currMember.setPath(path);
    }
}

DynamicArray<int> Genetic::performPMX(DynamicArray<int> &firstParent, DynamicArray<int> &secondParent) {
    size_t firstIndex{0}, secondIndex{0};

    while(firstIndex >= secondIndex)
    {
        firstIndex = RandomGenerator::getInt(0, firstParent.getSize() - 1);
        secondIndex = RandomGenerator::getInt(0, firstParent.getSize() - 1);
    }

    DynamicArray<int> child;

    for (int i = firstIndex; i <= secondIndex; ++i) {
        child.addBack(firstParent[i]);
    }

    for (int i = firstIndex; i <= secondIndex; ++i) {
        if(child.contains(secondParent[i])) {
            continue;
        }

        child.addFront(secondParent[i]);
    }

    for (int i = firstIndex; i >= 0; --i) {
        if(child.contains(secondParent[i])) {
            continue;
        }

        child.addFront(secondParent[i]);
    }

    for (int i = secondIndex; i < secondParent.getSize(); ++i) {
        if(child.contains(secondParent[i])) {
            continue;
        }

        child.addBack(secondParent[i]);
    }

    return child;
}

Path *Genetic::execute(AdjacencyMatrix &graph) {
    size_t citiesNumber = graph.getCitiesNumber();

    DynamicArray<int> optimalPath;
    size_t optimalCost{INT_MAX};

    LiteDynamicArray<Member> population;
    generateFirstPopulation(graph, population);

    population.sort();

    optimalPath = population[0].getPath();
    optimalCost = population[0].getCost();

    int iterationCounter = 0;
    int badIterationCounter = 0;

    while (iterationCounter < iterationNumber && badIterationCounter < xxx) {
        LiteDynamicArray<Member> newPopulation;

        crossover(population, newPopulation, graph);
        mutate(newPopulation);

        population = newPopulation;
        population.sort();

        std::cout << population[0].getCost() << std::endl;

        if (optimalCost > population[0].getCost()) {
            optimalCost = population[0].getCost();
            optimalPath = population[0].getPath();
            badIterationCounter = 0;
        } else {
            badIterationCounter++;
        }

        iterationCounter++;
    }

    auto returnPath = new Path(optimalPath, optimalCost);

    return returnPath;
}

void Genetic::testExecute(AdjacencyMatrix &graph) {

}