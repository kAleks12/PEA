//
// Created by kacper on 24.10.2022.
//

#include "../../inc/utils/FileManager.h"
#include <fstream>
#include <cmath>

std::map<std::string, int> *FileManager::solutions = nullptr;
int *FileManager::data = nullptr;
size_t FileManager::verticesNum = -1;

void FileManager::readSolutions(const std::string &fileName) {
    //Deleting old data
    delete[] solutions;

    //Opening source file
    std::ifstream srcFile(fileName);

    //Checking whether file exists
    if (!srcFile.is_open()) {
        return;
    }

    solutions = new std::map<std::string, int>;

    while (!srcFile.eof()) {
        std::string instanceName;
        int optimalCost;

        srcFile >> instanceName >> optimalCost;
        auto row = new std::pair<std::string, int>(instanceName, optimalCost);
        solutions->insert(*row);
        delete row;
    }

    srcFile.close();
}

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

void FileManager::saveData(const std::string &path, const std::list<TSP1_result> &resultData) {
    std::ofstream saveFile(path);

    for (const TSP1_result &result: resultData) {
        saveFile << result.instanceSize << ";" << result.time << "\n";
    }

    saveFile.close();
}

void FileManager::saveData(const std::string &path, const std::list<TSP2_result> &resultData) {
    std::ofstream saveFile(path);

    for (const TSP2_result &result: resultData) {
        saveFile << result.instanceName << ";" << result.avgResult << ";" << result.avgTime << "\n";
    }

    saveFile.close();
}