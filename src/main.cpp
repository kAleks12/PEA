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

#define var auto

int main() {
//    mkdir("TSP_tests");
//    Tests testEntity;
//    testEntity.sampleSize = 100;
//
//    testEntity.testBB(5, 30);
//    testEntity.testDP(5, 16);
//
//    Menu::initMenu();
    auto fileName = "tsp_17.txt";
    FileManager::readData(fileName);
    FileManager::readSolutions("solutions.txt");

    auto matrix = new AdjacencyMatrix(FileManager::verticesNum, FileManager::data);
    auto randomMatrix = MatrixGenerator::graph;

    Timer watch;
    SimulatedAnnealing sa;
    TabuSearch ts(0, 10, 20000);

    watch.start();
    var result1 =  sa.execute(*matrix);
    std::cout << "Execution time is: " << watch.getTime(MILLISECONDS) << "[ms]" << std::endl;
    std::cout << "Found path is: " << result1->toString() << std::endl;
    std::cout << "Error rate is: " << (((double) result1->getCost()/FileManager::solutions->at(fileName)) - 1) * 100 << "[%]\n";

    watch.start();
    var result2 =  ts.execute(*matrix);
    std::cout << "Execution time is: " << watch.getTime(MILLISECONDS) << "[ms]" << std::endl;
    std::cout << "Found path is: " << result2->toString() << std::endl;
    std::cout << "Error rate is: " << (((double) result2->getCost()/FileManager::solutions->at(fileName)) - 1) * 100 << "[%]";
}