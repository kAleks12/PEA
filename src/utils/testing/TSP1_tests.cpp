//
// Created by kacpe on 04.11.2022.
//

#include "../../../inc/utils/testing/TSP1_tests.h"
#include "../../../inc/utils/FileManager.h"
#include "../../../inc/utils/testing/MatrixGenerator.h"
#include "../../../inc/algorithms/BranchAndBound.h"
#include "../../../inc/algorithms/BruteForce.h"
#include "../../../inc/algorithms/DynamicProgramming.h"
#include "../../../inc/algorithms/SimulatedAnnealing.h"
#include "../../../inc/algorithms/TabuSearch.h"
#include <iostream>
#include <unistd.h>

AdjacencyMatrix *TSP1_tests::graph = nullptr;

//Function that calculates average time for provided list with intervals
double TSP1_tests::calcAvg(const std::list<double> &dataStr) {
    double avg = 0;

    //Calculating average from provided vector's elements
    for (double result: dataStr) {
        avg += result;
    }
    avg /= double(dataStr.size());

    return avg;
}

//Function that creates single series result and adds it to adequate list
void TSP1_tests::addSeriesAvg(double avg, int instanceSize, Algorithms alg) {
    TSP1_result result{};

    //Creating result object for specific structure and operation
    result.time = avg;
    result.instanceSize = instanceSize;

    //Adding created object to vector with all operations' results
    switch (alg) {
        case BF:
            bfResults.push_back(result);
            break;

        case DP:
            dpResults.push_back(result);
            break;

        case BB:
            bbResults.push_back(result);
            break;
    }
}

//Functions that tests all algorithms for matrix representation
void TSP1_tests::testAll(int start, int end) {
    testBF(start, end);
    testDP(start, end);
    testBB(start, end);
}

void TSP1_tests::testBB(int start, int end) {
    mkdir(basePath.c_str());

    //Creating operational variables
    std::list<double> intervals;

    BranchAndBound bbEntity;

    //Testing 7 different instanceSizes
    for (int vertices = start; vertices <= end; vertices++) {
        //100 times
        for (int i = 0; i < sampleSize; ++i) {
            //Generating new graph represented by matrix
            MatrixGenerator::createGraph(vertices, costRange);
            graph = MatrixGenerator::graph;

            //Measuring branch and bound algorithm
            timer.start();
            bbEntity.testExecute(*graph);
            intervals.push_back(timer.getTime(MICROSECONDS));
        }

        //Creating series results for current density
        addSeriesAvg(calcAvg(intervals), vertices, Algorithms::BB);

        //Clearing intervals for next density
        intervals.clear();

        std::cout << "Done instance size -  " << vertices << "\n";
    }

    //Saving results of all algorithms for current vertices number
    saveResultList("branch_and_bound", Algorithms::BB);


    //Clearing results for next vertices number
    bbResults.clear();
}

void TSP1_tests::testDP(int start, int end) {
    mkdir(basePath.c_str());

    //Creating operational variables
    std::list<double> intervals;

    DynamicProgramming dpEntity;

    //Testing 7 different instanceSizes
    for (int vertices = start; vertices <= end; vertices++) {
        //100 times
        for (int i = 0; i < sampleSize; ++i) {
            //Generating new graph represented by matrix
            MatrixGenerator::createGraph(vertices, costRange);
            graph = MatrixGenerator::graph;

            //Measuring branch and bound algorithm
            timer.start();
            dpEntity.testExecute(*graph);
            intervals.push_back(timer.getTime(MICROSECONDS));
        }

        //Creating series results for current density
        addSeriesAvg(calcAvg(intervals), vertices, Algorithms::DP);

        //Clearing intervals for next density
        intervals.clear();

        std::cout << "Done instance size -  " << vertices << "\n";
    }

    //Saving results of all algorithms for current vertices number
    saveResultList("dynamic_programming", Algorithms::DP);


    //Clearing results for next vertices number
    dpResults.clear();
}

void TSP1_tests::testBF(int start, int end) {
    mkdir(basePath.c_str());

    //Creating operational variables
    std::list<double> intervals;

    BruteForce bfEntity;

    //Testing 7 different instanceSizes
    for (int vertices = start; vertices <= end; vertices++) {
        //100 times
        for (int i = 0; i < sampleSize; ++i) {
            //Generating new graph represented by matrix
            MatrixGenerator::createGraph(vertices, costRange);
            graph = MatrixGenerator::graph;

            //Measuring branch and bound algorithm
            timer.start();
            bfEntity.testExecute(*graph);
            intervals.push_back(timer.getTime(MICROSECONDS));
        }

        //Creating series results for current density
        addSeriesAvg(calcAvg(intervals), vertices, Algorithms::BF);

        //Clearing intervals for next density
        intervals.clear();

        std::cout << "Done instance size -  " << vertices << "\n";
    }

    //Saving results of all algorithms for current vertices number
    saveResultList("brute_force", Algorithms::BF);


    //Clearing results for next vertices number
    bfResults.clear();
}

//Functions that saves measurements for a single algorithm to .txt file
void TSP1_tests::saveResultList(const std::string &algorithm, Algorithms alg) const  {
    //Creating write file path
    std::string path = basePath + algorithm + ".txt";

    switch (alg) {
        case BF:
            //Printing opResult objects for each tested operation to the file
            FileManager::saveData(path, bfResults);
            break;

        case BB:
            //Printing opResult objects for each tested operation to the file
            FileManager::saveData(path, bbResults);
            break;

        case DP:
            //Printing opResult objects for each tested operation to the file
            FileManager::saveData(path, dpResults);
            break;
        case SA:
            //Printing opResult objects for each tested operation to the file
            FileManager::saveData(path, saResults);
            break;
        case TS:
            //Printing opResult objects for each tested operation to the file
            FileManager::saveData(path, tsResults);
            break;
    }
}
