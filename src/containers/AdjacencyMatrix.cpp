//
// Created by kacpe on 20.10.2022.
//


#include <iostream>
#include "../../inc/containers/AdjacencyMatrix.h"

AdjacencyMatrix::AdjacencyMatrix(const AdjacencyMatrix &existingMatrix) {
    citiesNumber = existingMatrix.citiesNumber;

    allocate();
    copy(existingMatrix.getMatrix());
}

AdjacencyMatrix::AdjacencyMatrix(const size_t &verticesNumber, const int *edges) {
    this->citiesNumber = verticesNumber;
    allocate();
    initialize(edges);
}

AdjacencyMatrix::~AdjacencyMatrix() {
    this->deallocate();
}

void AdjacencyMatrix::allocate() {
    this->matrix = new int* [this->citiesNumber];

    for(int rowIterator = 0; rowIterator < this->citiesNumber; ++rowIterator)
    {
        this->matrix[rowIterator] = new int[this->citiesNumber];

        for(int columnIterator = 0; columnIterator < this->citiesNumber; ++columnIterator) {
            this->matrix[rowIterator][columnIterator] = 0;
        }
    }
}

void AdjacencyMatrix::deallocate() {
    if(this->matrix == nullptr) {
        return;
    }

    for(int rowIterator = 0; rowIterator < this->citiesNumber; ++rowIterator)
    {
        delete[] this->matrix[rowIterator];
    }

    delete[] this->matrix;
    this->matrix = nullptr;
}

void AdjacencyMatrix::initialize(const int *edges) {
    int index = 0;

    for(int rowsIterator = 0; rowsIterator < this->citiesNumber; ++rowsIterator)
    {
        for(int columnIterator = 0; columnIterator < this->citiesNumber; ++columnIterator)
        {
            this->matrix[rowsIterator][columnIterator] = edges[index];
            index++;
        }
    }
}

void AdjacencyMatrix::copy(int **existingMatrix) {
    for(int rowsIterator = 0; rowsIterator < this->citiesNumber; ++rowsIterator)
    {
        for(int columnIterator = 0; columnIterator < this->citiesNumber; ++columnIterator)
        {
            this->matrix[rowsIterator][columnIterator] =
                    existingMatrix[rowsIterator][columnIterator];
        }
    }
}

void AdjacencyMatrix::print() {
    std::cout << "Adjacency matrix:\n";

    for(int rowsIterator = 0; rowsIterator < this->citiesNumber; ++rowsIterator)
    {
        for(int columnIterator = 0; columnIterator < this->citiesNumber; ++columnIterator)
        {
            std::cout << "| " << matrix[rowsIterator][columnIterator] << " ";
        }

        std::cout << "|\n";
    }
}
