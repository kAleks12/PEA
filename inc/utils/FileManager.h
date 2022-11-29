//
// Created by kacper on 24.10.2022.
//
#pragma once

#include "testing/Tests.h"
#include <string>
#include "../../inc/containers/DynamicArray.hpp"
#include <map>

class FileManager {
public:
    //Class variables
    static int *data;
    static std::map<std::string, int> *solutions;
    static size_t verticesNum;

    static void readData(const std::string &fileName); //assigns data and verticesNum members with data from file
    static void readSolutions(const std::string &fileName); //assigns data and verticesNum members with data from file
    static void saveData(const std::string &fileName, const std::list<OpResult> &data); //saves list to specified file
};
