//
// Created by kacpe on 24.10.2022.
//
#pragma once

#include <cstdio>
#include <string>

class FileManager {
public:
    static int* data;
    static size_t verticesNum;
    static void readData(const std::string & fileName);
};
