//
// Created by kacpe on 10.01.2023.
//

#include "../../../inc/algorithms/utils/GeneticHelper.h"
#include "../../../inc/utils/RandomGenerator.h"



void GeneticHelper::swapMutation(LiteDynamicArray <size_t> &path) {
    size_t firstIndex;
    size_t secondIndex;
    RandomGenerator::generatePair(firstIndex, secondIndex, path.getSize());

    path.swap(firstIndex, secondIndex);
}

void GeneticHelper::insertMutation(LiteDynamicArray <size_t> &path) {
    size_t firstIndex;
    size_t secondIndex;
    RandomGenerator::generatePair(firstIndex, secondIndex, path.getSize());

    auto temp = path[secondIndex];
    path.remove(secondIndex);
    path.add(firstIndex, temp);
}

void GeneticHelper::invertMutation(LiteDynamicArray <size_t> &path) {
    size_t firstIndex;
    size_t secondIndex;
    RandomGenerator::generatePair(firstIndex, secondIndex, path.getSize());

    while (firstIndex < secondIndex) {
        path.swap(firstIndex, secondIndex);
        firstIndex++;
        secondIndex--;
    }
}

void GeneticHelper::scrambleMutation(LiteDynamicArray <size_t> &path) {
    size_t firstIndex;
    size_t secondIndex;
    RandomGenerator::generatePair(firstIndex, secondIndex, path.getSize());

    int swapNumber = secondIndex - firstIndex;

    for (int i = 0; i < swapNumber; i++) {
        auto firstSwapIndex = RandomGenerator::getInt(firstIndex, secondIndex);
        auto secondSwapIndex = RandomGenerator::getInt(firstIndex, secondIndex);

        path.swap(firstSwapIndex, secondSwapIndex);
    }
}

LiteDynamicArray <size_t> GeneticHelper::OXCrossover(LiteDynamicArray <size_t> &firstParent,
                                               LiteDynamicArray <size_t> &secondParent) {
    LiteDynamicArray <size_t> result;
    size_t firstIndex;
    size_t secondIndex;
    RandomGenerator::generatePair(firstIndex, secondIndex, firstParent.getSize());

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

