//
// Created by kacper on 24.10.2022.
//

#include "../../inc/utils/FileManager.h"
#include <fstream>
#include <cmath>

int *FileManager::data = nullptr;
size_t FileManager::verticesNum = -1;

void FileManager::readData(const std::string &fileName) {
    //Deleting old data
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

    //Filling the data array with numbers from source file
    for (int index = 0; index < lastIndex; index++) {
        srcFile >> tmp;
        data[index] = std::stoi(tmp);
    }

    srcFile.close();
}

void FileManager::saveData(const std::string &path, const std::list<OpResult> &resultData) {
    std::ofstream saveFile(path);

    for (const OpResult &result: resultData) {
        saveFile << result.instanceSize << ";" << result.time << "\n";
    }

    saveFile.close();
}