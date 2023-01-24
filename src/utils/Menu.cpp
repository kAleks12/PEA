//
// Created by kacper on 02.11.2022.
//

//#include <cstdlib>
#include <iostream>
#include "../../inc/utils/Menu.h"
#include "../../inc/algorithms/BruteForce.h"
#include "../../inc/algorithms/DynamicProgramming.h"
#include "../../inc/algorithms/BranchAndBound.h"
#include "../../inc/utils/FileManager.h"
#include "../../inc/utils/testing/MatrixGenerator.h"
#include "../../inc/algorithms/SimulatedAnnealing.h"
#include "../../inc/algorithms/TabuSearch.h"
#include "../../inc/algorithms/Genetic.h"

AdjacencyMatrix *Menu::graph = nullptr;

void Menu::readGraph() {
    system("cls");
    std::string fileName;

    std::cout << "Enter name of the file eg. \"data.txt\"\n(must be located in the same directory as .exe file): ";
    std::cin >> fileName;

    FileManager::readData(fileName);

    if (FileManager::data == nullptr) {
        system("cls");

        std::cout << "File not found!\n";
        system("Pause");
        return;
    }

    delete graph;
    graph = new AdjacencyMatrix(FileManager::verticesNum, FileManager::data);
}

void Menu::generateGraph() {
    system("cls");
    std::string size;

    std::cout << "Enter size of the graph (If graph is already read, it will be overwritten!): ";
    std::cin >> size;

    try {
        auto graphSize = std::stoi(size);

        if (graphSize <= 0) {
            system("cls");
            std::cout << "Provided size must be greater than 0!\n";
            system("Pause");
        }

        MatrixGenerator::createGraph(graphSize);
        graph = MatrixGenerator::graph;

    } catch (std::exception &e) {
        system("cls");
        std::cout << "Provided size is not a number!\n";
        system("Pause");
    }
}

void Menu::displayGraph() {
    system("cls");

    if (graph == nullptr) {
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

        std::cout << "[0] TSP1\n";
        std::cout << "[1] TSP2\n";
        std::cout << "[2] TSP3\n";
        std::cout << "Exit program [Q]\n\n";
        std::cout << "Hello, select option: ";

        std::cin >> input;

        switch (input) {
            case '0':
                tsp1Menu();
                break;
            case '1':
                tsp2Menu();
                break;
            case '2':
                tsp3Menu();
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

void Menu::tsp1Menu() {
//Displaying initial menu with available options
    char input;

    while (true) {
        system("cls");

        std::cout << "[0] Read graph\n";
        std::cout << "[1] Generate random graph\n";
        std::cout << "[2] Display graph\n";
        std::cout << "[3] Brute force\n";
        std::cout << "[4] Dynamic programming\n";
        std::cout << "[5] Branch and bound\n";
        std::cout << "Exit program [Q]\n\n";
        std::cout << "Hello, select option: ";

        std::cin >> input;

        switch (input) {
            case '0':
                readGraph();
                break;
            case '1':
                generateGraph();
                break;
            case '2':
                displayGraph();
                break;
            case '3':
                runAlgorithm(Algorithms::BF);
                break;
            case '4':
                runAlgorithm(Algorithms::DP);
                break;
            case '5':
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

void Menu::tsp2Menu() {
//Displaying initial menu with available options
    char input;

    while (true) {
        system("cls");

        std::cout << "[0] Read graph\n";
        std::cout << "[1] Generate random graph\n";
        std::cout << "[2] Display graph\n";
        std::cout << "[3] Simulated annealing\n";
        std::cout << "[4] Tabu search\n";
        std::cout << "Exit program [Q]\n\n";
        std::cout << "Hello, select option: ";

        std::cin >> input;

        switch (input) {
            case '0':
                readGraph();
                break;
            case '1':
                generateGraph();
                break;
            case '2':
                displayGraph();
                break;
            case '3':
                runAlgorithm(Algorithms::SA);
                break;
            case '4':
                runAlgorithm(Algorithms::TS);
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

void Menu::tsp3Menu() {
//Displaying initial menu with available options
    char input;

    while (true) {
        system("cls");

        std::cout << "[0] Read graph\n";
        std::cout << "[1] Generate random graph\n";
        std::cout << "[2] Display graph\n";
        std::cout << "[3] Perform genetic algorithm\n";
        std::cout << "Exit program [Q]\n\n";
        std::cout << "Hello, select option: ";

        std::cin >> input;

        switch (input) {
            case '0':
                readGraph();
                break;
            case '1':
                generateGraph();
                break;
            case '2':
                displayGraph();
                break;
            case '3':
                runGenetic();
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

    if (algorithm == TS) {
        int size;
        int iterations;
        int neighbourSize;
        std::cout << "Please enter size of tabu list: ";
        std::cin >> size;

        std::cout << "Please enter number of iterations: ";
        std::cin >> iterations;

        std::cout << "Please enter size of neighbour list: ";
        std::cin >> neighbourSize;

        TabuSearch tsEntity(iterations, size, neighbourSize);
        std::cout << tsEntity.execute(*graph)->toString() << std::endl;
        system("Pause");
        return;
    }

    if (algorithm == SA) {
        int temperature;
        double coolingRate;

        std::cout << "Please enter starting temperature: ";
        std::cin >> temperature;

        std::cout << "Please enter cooling rate: ";
        std::cin >> coolingRate;

        SimulatedAnnealing saEntity(temperature, coolingRate);
        std::cout << saEntity.execute(*graph)->toString() << std::endl;
        system("Pause");
        return;
    }

    BruteForce bfEntity;
    BranchAndBound bbEntity;
    DynamicProgramming dpEntity;

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

void Menu::runGenetic() {
    system("cls");

    if (graph == nullptr) {
        std::cout << "Please read graph first!\n";
        system("Pause");

        return;
    }


    float mutationRate;
    float crossoverRate;
    float alphaSize;
    int iterationNumber;
    int populationSize;
    double coolingRate;

    std::cout << "Please enter mutation rate: ";
    std::cin >> mutationRate;

    std::cout << "Please enter crossover rate: ";
    std::cin >> crossoverRate;

    std::cout << "Please enter alpha size rate: ";
    std::cin >> alphaSize;

    std::cout << "Please enter iteration number: ";
    std::cin >> iterationNumber;

    std::cout << "Please enter population number: ";
    std::cin >> populationSize;

    Genetic genEntity;
    genEntity.setCrossoverRate(crossoverRate);
    genEntity.setMutationRate(mutationRate);
    genEntity.setPopulationSize(populationSize);
    genEntity.setAlphaSize(alphaSize);
    genEntity.setPopulationNumber(iterationNumber);

    std::cout << "\n\nPlease choose mutation type:\n";
    std::cout << "[0] Invert\n";
    std::cout << "[1] Swap\n";
    std::cout << "[2] Scramble\n";
    std::cout << "[3] Insert\n";
    std::cout << "[other] default\n";

    char input;
    std::cin >> input;

    switch (input) {
        case '0':
            genEntity.setMutationType(Invert);
            break;
        case '1':
            genEntity.setMutationType(Swap);
            break;
        case '2':
            genEntity.setMutationType(Scramble);
            break;
        case '3':
            genEntity.setMutationType(Insert);
            break;

        default:
            break;
    }

    std::cout << genEntity.execute(*graph)->toString() << std::endl;
    system("Pause");
}