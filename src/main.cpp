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
#include "../inc/containers/LiteDynamicArray.h"
#include "../inc/containers/Member.h"
#include "../inc/algorithms/Genetic.h"

#define var auto

int main() {
   Menu::initMenu();
//    var fileName = "tsp_152.txt";
//    FileManager::readData(fileName);
//    FileManager::readSolutions("solutions.txt");
//    auto matrix = new AdjacencyMatrix(FileManager::verticesNum, FileManager::data);
//    Genetic entity;
//
//    entity.setCrossoverRate(0.1);
//    var result = entity.execute(*matrix);
//    var bestResult = FileManager::solutions->at(fileName);
//    std::cout << "Error rate: " << (((float) result->getCost() / bestResult) - 1) * 100.00 << "[%]" << std::endl;

}