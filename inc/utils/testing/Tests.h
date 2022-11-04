//
// Created by kacpe on 04.11.2022.
//

#pragma once

#include <list>
#include <string>
#include "../../containers/AdjacencyMatrix.h"
#include "../Enums.h"
#include "Timer.h"

//Helping structure for individual results
struct OpResult {
    double time;
    size_t instanceSize;
};


class Tests {
    //Class variables
    static AdjacencyMatrix *graph;

    Timer timer;
    std::list<OpResult> bfResults;
    std::list<OpResult> dpResults;
    std::list<OpResult> bbResults;

public:
    size_t sampleSize = 100;
    int costRange = 100;
    std::string basePath = "TSP_tests\\";

    //Class methods
    static double calcAvg(const std::list<double> &); //Calculate average time from list elements
    void addSeriesAvg(double avg, int instanceSize, Algorithms alg); //Add avg time to adequate result list
    void test(); //Perform testing for all algorithms in matrix representation
    void saveResultList(const std::string &algorithm, Algorithms alg) const; //Save results an algorithm to file
};