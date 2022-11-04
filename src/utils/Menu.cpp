//
// Created by kacper on 02.11.2022.
//

#include <cstdlib>
#include <iostream>
#include "../../inc/utils/Menu.h"
#include "../../inc/algorithms/BruteForce.h"
#include "../../inc/algorithms/DynamicProgramming.h"
#include "../../inc/algorithms/BranchAndBound.h"
#include "../../inc/utils/FileManager.h"

AdjacencyMatrix *Menu::graph = nullptr;

void Menu::readGraph() {
    system("cls");
    std::string fileName;

    std::cout << "Enter name of the file eg. \"data.txt\"\n(must be located in the same directory as .exe file): ";
    std::cin >> fileName;

    FileManager::readData(fileName);

    if(FileManager::data == nullptr) {
        system("cls");

        std::cout << "File not found!\n";
        system("Pause");
        return;
    }

    delete graph;
    graph = new AdjacencyMatrix(FileManager::verticesNum, FileManager::data);
}

void Menu::displayGraph() {
    system("cls");

    if(graph == nullptr) {
        std::cout << "Please read graph first!\n";
        system("Pause");

        return;
    }

    graph->print();

    std::cout << std::endl;
    system("Pause");
}

void Menu::initMenu() {
    //Displaying initial menu with available options
    char input;

    while (true) {
        system("cls");

        std::cout << "[0] Read graph\n";
        std::cout << "[1] Display graph\n";
        std::cout << "[2] Brute force\n";
        std::cout << "[3] Dynamic programming\n";
        std::cout << "[4] Branch and bound\n";
        std::cout << "Exit program [Q]\n\n";
        std::cout << "Hello, select option: ";

        std::cin >> input;

        switch (input) {
            case '0':
                readGraph();
                break;
            case '1':
                displayGraph();
                break;
            case '2':
                runAlgorithm(Algorithms::BF);
                break;
            case '3':
                runAlgorithm(Algorithms::DP);
                break;
            case '4':
                runAlgorithm(Algorithms::BB);
                break;

            case 'Q':
                return;
            case 'q':
                return;

            default:
                break;
        }
    }
}

void Menu::runAlgorithm(Algorithms algorithm) {
    system("cls");

    if (graph == nullptr) {
        std::cout << "Please read graph first!\n";
        system("Pause");

        return;
    }

    BruteForce bfEntity;
    DynamicProgramming dpEntity;
    BranchAndBound bbEntity;

    switch (algorithm) {
        case BF:
            std::cout << bfEntity.execute(*graph)->toString() << std::endl;
            system("Pause");
            break;

        case DP:
            std::cout << dpEntity.execute(*graph)->toString() << std::endl;
            system("Pause");
            break;

        case BB:
            std::cout << bbEntity.execute(*graph)->toString() << std::endl;
            system("Pause");
            break;
    }
}