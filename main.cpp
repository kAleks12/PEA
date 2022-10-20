#include <iostream>
#include "inc/AdjacencyMatrix.h"

int main() {
    int edges[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto matrix = new AdjacencyMatrix(3, edges);
    matrix->print();

}
