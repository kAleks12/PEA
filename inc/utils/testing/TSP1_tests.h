//
// Created by kacpe on 04.11.2022.
//

#pragma once

#include "../../containers/AdjacencyMatrix.h"
#include "../Enums.h"
#include "Timer.h"
#include <list>
#include <string>

//Helping structure for individual results
struct TSP1_result {
    double time;
    size_t instanceSize;
};


class TSP1_tests {
    //Class variables
    static AdjacencyMatrix *graph;

    Timer timer;
    std::list<TSP1_result> bfResults;
    std::list<TSP1_result> dpResults;
    std::list<TSP1_result> bbResults;
    std::list<TSP1_result> saResults;
    std::list<TSP1_result> tsResults;

    void saveResultList(const std::string &algorithm, Algorithms alg) const; //Save results an algorithm to file
    void addSeriesAvg(double avg, int instanceSize, Algorithms alg); //Add avg time to adequate result list
    static double calcAvg(const std::list<double> &); //Calculate average time from list elements

public:
    size_t sampleSize = 100;
    int costRange = 100;
    std::string basePath = "TSP1_tests\\";

    //Class methods
    void testAll(int start, int end); //Perform testing for all algorithms in matrix representation
    void testBB(int start, int end);
    void testDP(int start, int end);
    void testBF(int start, int end);

};