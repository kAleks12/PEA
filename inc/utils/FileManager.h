//
// Created by kacper on 24.10.2022.
//
#pragma once

#include "testing/TimeTests.h"
#include <string>
#include "../../inc/containers/DynamicArray.hpp"
#include "testing/ErrorTests.h"
#include "../../src/utils/testing/GeneticTests.h"
#include <map>

class FileManager {
public:
    //Class variables
    static int *data;
    static std::map<std::string, int> *solutions;
    static size_t verticesNum;

    static void readData(const std::string &fileName); //assigns data and verticesNum members with data from file
    static int readGenData(const std::string &fileName); //assigns data and verticesNum members with data from file
    static void readSolutions(const std::string &fileName); //assigns data and verticesNum members with data from file
    static void saveData(const std::string &fileName, const std::list<TimeResult> &data); //saves list to specified file
    static void saveData(const std::string &fileName, const std::list<ErrorResult> &data); //saves list to specified file
    static void saveData(const std::string &fileName, const std::list<GeneticResult> &data); //saves list to specified file
};
