//
// Created by kacpe on 17.01.2023.
//

#pragma once


#include <string>
#include <list>
#include "../../../inc/containers/AdjacencyMatrix.h"

struct GenInstance {
    AdjacencyMatrix graph;
    std::string name;
    int bestResult;
};

struct GeneticResult {
    double avgTime;
    double avgError;
    std::string instanceName;
};

class GeneticTests {
    std::list <GenInstance> instances;
    std::list<GeneticResult> results;

    static double calcAvg(const std::list<double> &); //Calculate average time from list elements
    static double calcAvg(const std::list<int> &); //Calculate average time from list elements

    void loadInstances();
    void addSeriesAvg(double avgTime, double avgError, std::string instanceName);
    void saveResultList(const std::string &name) const; //Save results an algorithm to file

public :
    size_t sampleSize = 10;
    std::string outputPath = "Genetic_tests\\";
    std::string inputPath = "input//";

    void testPopulation();
    void testMutation();
    void testCrossover();
};