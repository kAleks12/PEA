//
// Created by kacpe on 03.11.2022.
//

#include "../../inc/utils/MatrixGenerator.h"
#include <random>

AdjacencyMatrix* MatrixGenerator::graph = nullptr;

 void MatrixGenerator::createGraph(int instanceSize) {
    delete graph;

    int** distances = new int *[instanceSize];
    for (int i = 0; i < instanceSize; i++) {
        distances[i] = new int[instanceSize];
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> range(1, 100);

    for (int i = 0; i < instanceSize; i++) {
        for (int j = 0; j < instanceSize; j++) {
            //Creating matrix diagonal
            if(j == i) {
                distances[i][j] = -1;
                continue;
            }

            //Ensuring there will be Hamilton's cycle
            if(j == i + 1) {
                distances[i][j] = 110;
                continue;
            }


            distances[i][j] = range(gen);
        }
    }

    graph = new AdjacencyMatrix(instanceSize, distances);
}
