//
// Created by kacpe on 05.12.2022.
//

#include <utility>

#include "../../../inc/utils/testing/TSP2_tests.h"
#include "../../../inc/utils/FileManager.h"
#include "../../../inc/algorithms/SimulatedAnnealing.h"
#include "../../../inc/algorithms/TabuSearch.h"

void TSP2_tests::testAll() {
    testSA();
    testTS();
}

void TSP2_tests::testSA() {
    loadInstances();

    //Creating operational variables
    std::list<double> timeResults;
    std::list<int> results;
    Timer timer;

    SimulatedAnnealing saEntity;

    //Testing 7 different instanceSizes
    for (auto instance: instances) {
        for (int i = 0; i < sampleSize; ++i) {
            timer.start();
            auto result = saEntity.execute(instance.graph);
            auto time = timer.getTime(MILLISECONDS);

            timeResults.push_back(time);
            results.push_back(result->getCost());

            delete result;
        }
        //Creating series results for current density
        addSeriesAvg(calcAvg(timeResults), calcAvg(results), instance.name, Algorithms::SA);
    }

    //Clearing intervals for next density
    timeResults.clear();
    results.clear();

    //Saving results of all algorithms for current vertices number
    saveResultList("simulated_annealing", Algorithms::SA);


    //Clearing results for next vertices number
    saResults.clear();
}

void TSP2_tests::testTS() {
    loadInstances();

    //Creating operational variables
    std::list<double> timeResults;
    std::list<int> results;
    Timer timer;

    TabuSearch tsEntity;

    //Testing 7 different instanceSizes
    for (auto instance: instances) {
        for (int i = 0; i < sampleSize; ++i) {
            timer.start();
            auto result = tsEntity.execute(instance.graph);
            auto time = timer.getTime(MILLISECONDS);

            timeResults.push_back(time);
            results.push_back(result->getCost());

            delete result;
        }
        //Creating series results for current density
        addSeriesAvg(calcAvg(timeResults), calcAvg(results), instance.name, Algorithms::TS);
    }

    //Clearing intervals for next density
    timeResults.clear();
    results.clear();

    //Saving results of all algorithms for current vertices number
    saveResultList("tabu_search", Algorithms::TS);


    //Clearing results for next vertices number
    tsResults.clear();
}

double TSP2_tests::calcAvg(const std::list<double> &dataStr) {
    double avg = 0;

    //Calculating average from provided vector's elements
    for (double result: dataStr) {
        avg += result;
    }
    avg /= double(dataStr.size());

    return avg;
}

double TSP2_tests::calcAvg(const std::list<int> &dataStr) {
    double avg = 0;

    //Calculating average from provided vector's elements
    for (int result: dataStr) {
        avg += result;
    }
    avg /= (double) dataStr.size();

    return avg;
}

void TSP2_tests::addSeriesAvg(double avgTime, double avgResult, std::string instanceName, Algorithms alg) {
    TSP2_result result{};

    //Creating result object for specific structure and operation
    result.avgTime = avgTime;
    result.avgResult = avgResult;
    result.instanceName = std::move(instanceName);

    //Adding created object to vector with all operations' results
    switch (alg) {
        case SA:
            saResults.push_back(result);
            break;
        case TS:
            tsResults.push_back(result);
            break;
        default:
            break;
    }
}

void TSP2_tests::saveResultList(const std::string &algorithm, Algorithms alg) const {
    //Creating write file path
    std::string path = outputPath + algorithm + ".txt";

    switch (alg) {
        case SA:
            //Printing opResult objects for each tested operation to the file
            FileManager::saveData(path, saResults);
            break;
        case TS:
            //Printing opResult objects for each tested operation to the file
            FileManager::saveData(path, tsResults);
            break;
        default:
            break;
    }
}

void TSP2_tests::loadInstances() {
    if (!instances.empty()) {
        return;
    }

    for (const auto &entry: std::filesystem::directory_iterator(inputPath)) {
        const auto &path = entry.path();

        if (path.extension().string() != ".txt") {
            continue;
        }

        FileManager::readData(path.string());

        Instance newInstance;
        newInstance.graph = *new AdjacencyMatrix(FileManager::verticesNum, FileManager::data);
        newInstance.name = path.filename().string();

        instances.push_back(newInstance);
    }
}


