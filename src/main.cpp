#include <iostream>
#include <algorithm>
#include <unistd.h>
#include "../inc/containers/AdjacencyMatrix.h"
#include "../inc/utils/FileManager.h"
#include "../inc/utils/Menu.h"
#include "../inc/algorithms/BranchAndBound.h"
#include "../inc/algorithms/DynamicProgramming.h"
#include "../inc/utils/RandomGenerator.h"
#include "../inc/algorithms/SimulatedAnnealing.h"
#include "../inc/utils/testing/MatrixGenerator.h"
#include "../inc/algorithms/TabuSearch.h"
#include "../inc/utils/testing/ErrorTests.h"

#define var auto

int main() {
//   Menu::initMenu();

    TimeTests tests1;
    tests1.sampleSize = 10;
    tests1.testTS(20, 80, 10);

//    ErrorTests tests;
//    tests.sampleSize = 10;
//    tests.testAll();
}