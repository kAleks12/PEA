//
// Created by kacpe on 17.01.2023.
//

#include <direct.h>

#include <utility>
#include "GeneticTests.h"
#include "../../../inc/utils/testing/Timer.h"
#include "../../../inc/algorithms/Genetic.h"
#include "../../../inc/utils/FileManager.h"


void GeneticTests::testPopulation() {
    loadInstances();
    mkdir(outputPath.c_str());

    //Creating operational variables
    std::list<double> timeResults;
    std::list<double> errorResults;
    Timer timer;

    Genetic genEntity;

    genEntity.setCrossoverRate(0.5);
    genEntity.setMutationRate(0.5);
    //Testing 7 different instanceSizes

    genEntity.setMutationType(Invert);

    for (int population = 100; population <= 300; population += 100) {
        genEntity.setPopulationSize(population);


        for (auto instance: instances) {
            for (int i = 0; i < sampleSize; i++) {
                timer.start();
                auto result = genEntity.execute(instance.graph);
                auto time = timer.getTime(MILLISECONDS);

                timeResults.push_back(time);
                auto error = (((double) result->getCost() / instance.bestResult) - 1) * 100;
                errorResults.push_back(error);

                delete result;
            }
            //Creating series results for current density
            addSeriesAvg(
                    calcAvg(timeResults), calcAvg(errorResults),
                    instance.name + "-" + std::to_string(population) + "-invert"
            );

            timeResults.clear();
            errorResults.clear();
        }
    }

    genEntity.setMutationType(Scramble);

    for (int population = 100; population <= 300; population += 100) {
        genEntity.setPopulationSize(population);


        for (auto instance: instances) {
            for (int i = 0; i < sampleSize; i++) {
                timer.start();
                auto result = genEntity.execute(instance.graph);
                auto time = timer.getTime(MILLISECONDS);

                timeResults.push_back(time);
                auto error = (((double) result->getCost() / instance.bestResult) - 1) * 100;
                errorResults.push_back(error);

                delete result;
            }
            //Creating series results for current density
            addSeriesAvg(
                    calcAvg(timeResults), calcAvg(errorResults),
                    instance.name + "-" + std::to_string(population) + "-scramble"
            );

            timeResults.clear();
            errorResults.clear();
        }
    }

    //Saving results of all algorithms for current vertices number
    auto name = "genetic-population";
    saveResultList(name);


    //Clearing results for next vertices number
    results.clear();
}

void GeneticTests::testCrossover() {
    loadInstances();
    mkdir(outputPath.c_str());

    //Creating operational variables
    std::list<double> timeResults;
    std::list<double> errorResults;
    Timer timer;

    Genetic genEntity;
    genEntity.setMutationRate(0.5);
    genEntity.setPopulationSize(300);

    //Testing 7 different instanceSizes

    genEntity.setMutationType(Invert);

    for (double rate = 0.3; rate <= 0.9; rate += 0.3) {
        genEntity.setCrossoverRate(rate);

        for (auto instance: instances) {
            for (int i = 0; i < sampleSize; i++) {
                timer.start();
                auto result = genEntity.execute(instance.graph);
                auto time = timer.getTime(MILLISECONDS);

                timeResults.push_back(time);
                auto error = (((double) result->getCost() / instance.bestResult) - 1) * 100;
                errorResults.push_back(error);

                delete result;


            }
            //Creating series results for current density
            addSeriesAvg(
                    calcAvg(timeResults), calcAvg(errorResults),
                    instance.name + "-" + std::to_string(rate) + "-invert"
            );

            timeResults.clear();
            errorResults.clear();
        }
    }

    genEntity.setMutationType(Scramble);

    for (float rate = 0.3; rate < 1; rate += 0.3) {
        genEntity.setCrossoverRate(rate);

        for (auto instance: instances) {
            for (int i = 0; i < sampleSize; i++) {
                timer.start();
                auto result = genEntity.execute(instance.graph);
                auto time = timer.getTime(MILLISECONDS);

                timeResults.push_back(time);
                auto error = (((double) result->getCost() / instance.bestResult) - 1) * 100;
                errorResults.push_back(error);

                delete result;


            }
            //Creating series results for current density
            addSeriesAvg(
                    calcAvg(timeResults), calcAvg(errorResults),
                    instance.name + "-" + std::to_string(rate) + "-scramble"
            );

            timeResults.clear();
            errorResults.clear();
        }
    }

    //Saving results of all algorithms for current vertices number
    auto name = "genetic-crossover";
    saveResultList(name);


    //Clearing results for next vertices number
    results.clear();
}

void GeneticTests::testMutation() {
    loadInstances();
    mkdir(outputPath.c_str());

    //Creating operational variables
    std::list<double> timeResults;
    std::list<double> errorResults;
    Timer timer;

    Genetic genEntity;
    genEntity.setCrossoverRate(0.5);
    genEntity.setPopulationSize(300);

    //Testing 7 different instanceSizes

    genEntity.setMutationType(Invert);

    for (double rate = 0.3; rate <= 0.9; rate += 0.3) {
        genEntity.setMutationRate(rate);
        for (auto instance: instances) {
            for (int i = 0; i < sampleSize; i++) {
                timer.start();
                auto result = genEntity.execute(instance.graph);
                auto time = timer.getTime(MILLISECONDS);

                timeResults.push_back(time);
                auto error = (((double) result->getCost() / instance.bestResult) - 1) * 100;
                errorResults.push_back(error);

                delete result;


            }
            //Creating series results for current density
            addSeriesAvg(
                    calcAvg(timeResults), calcAvg(errorResults),
                    instance.name + "-" + std::to_string(rate) + "-invert"
            );

            timeResults.clear();
            errorResults.clear();
        }
    }

    genEntity.setMutationType(Scramble);

    for (float rate = 0.3; rate < 1; rate += 0.3) {
        genEntity.setMutationRate(rate);
        for (auto instance: instances) {
            for (int i = 0; i < sampleSize; i++) {
                timer.start();
                auto result = genEntity.execute(instance.graph);
                auto time = timer.getTime(MILLISECONDS);

                timeResults.push_back(time);
                auto error = (((double) result->getCost() / instance.bestResult) - 1) * 100;
                errorResults.push_back(error);

                delete result;


            }
            //Creating series results for current density
            addSeriesAvg(
                    calcAvg(timeResults), calcAvg(errorResults),
                    instance.name + "-" + std::to_string(rate) + "-scramble"
            );

            timeResults.clear();
            errorResults.clear();
        }
    }



    //Saving results of all algorithms for current vertices number
    auto name = "genetic-mutation";
    saveResultList(name);


    //Clearing results for next vertices number
    results.clear();
}

double GeneticTests::calcAvg(const std::list<double> &dataStr) {
    double avg = 0;

    //Calculating average from provided vector's elements
    for (double result: dataStr) {
        avg += result;
    }
    avg /= double(dataStr.size());

    return avg;
}

void GeneticTests::addSeriesAvg(double avgTime, double avgResult, std::string instanceName) {
    GeneticResult result{};

    //Creating result object for specific structure and operation
    result.avgTime = avgTime;
    result.avgError = avgResult;
    result.instanceName = std::move(instanceName);

    //Adding created object to vector with all operations' results

    results.push_back(result);
}

void GeneticTests::saveResultList(const std::string &testName) const {
    //Creating write file path
    std::string path = outputPath + testName + ".txt";

    //Printing opResult objects for each tested operation to the file
    FileManager::saveData(path, results);
}

void GeneticTests::loadInstances() {
    if (!instances.empty()) {
        return;
    }

    for (const auto &entry: std::experimental::filesystem::directory_iterator(inputPath)) {
        const auto &path = entry.path();

        if (path.extension().string() != ".txt") {
            continue;
        }

        auto bestResult = FileManager::readGenData(path.string());

        GenInstance newInstance;
        newInstance.graph = *new AdjacencyMatrix(FileManager::verticesNum, FileManager::data);
        newInstance.name = path.filename().string();
        newInstance.bestResult = bestResult;

        instances.push_back(newInstance);
    }
}