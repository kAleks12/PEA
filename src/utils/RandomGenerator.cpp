//
// Created by kacpe on 29.11.2022.
//

#include "../../inc/utils/RandomGenerator.h"

std::mt19937 RandomGenerator::gen((std::random_device()) ());

int RandomGenerator::getInt(int high) {
    std::uniform_int_distribution<int> range(0, high);

    return range(gen);
}

int RandomGenerator::getInt(int low, int high) {
    std::uniform_int_distribution<int> range(low, high);

    return range(gen);
}

double RandomGenerator::getDouble(double high) {
    std::uniform_real_distribution<double> range(0, high);

    return range(gen);
}

double RandomGenerator::getDouble(double low, double high) {
    std::uniform_real_distribution<double> range(low, high);

    return range(gen);
}

void RandomGenerator::generatePair(size_t &firstIndex, size_t &secondIndex, int upperBound) {
    do {
        firstIndex = RandomGenerator::getInt(0, upperBound - 2);
        secondIndex = RandomGenerator::getInt(0, upperBound - 1);
    } while (firstIndex >= secondIndex);
}
