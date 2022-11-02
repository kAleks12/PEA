//
// Created by kacpe on 24.10.2022.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include "../../inc/utils/FileManager.h"

int *FileManager::data = nullptr;
size_t FileManager::verticesNum = -1;

void FileManager::readData(const std::string &fileName) {
    delete[] data;
    //Opening source file
    std::ifstream srcFile(fileName);

    //Checking whether file exists
    if (!srcFile.is_open()) {
        return;
    }

    srcFile >> FileManager::verticesNum;

    FileManager::data = new int[verticesNum * verticesNum];
    std::string tmp;
    auto lastIndex = powl(FileManager::verticesNum, 2);

    //Filling the array with data from source file
    for (int index = 0; index < lastIndex; index++) {
        srcFile >> tmp;
        data[index] = std::stoi(tmp);
    }

    srcFile.close();
}