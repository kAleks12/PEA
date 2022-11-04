//
// Created by kacper on 24.10.2022.
//
#pragma once

#include <cstdio>
#include <string>
#include "testing/Tests.h"

class FileManager {
public:
    //Class variables
    static int* data;
    static size_t verticesNum;

    static void readData(const std::string & fileName); //assigns data and verticesNum members with data from file
    static void saveData(const std::string &fileName, const std::list<OpResult> &data); //saves list to specified file
};
