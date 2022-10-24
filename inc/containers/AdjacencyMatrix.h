//
// Created by kacpe on 20.10.2022.
//

#pragma once

#include <cstdio>

class AdjacencyMatrix
{
    size_t citiesNumber;
    int **matrix = nullptr;

    void allocate();
    void deallocate();

    void initialize(const int* edges);
    void copy(int** existingMatrix);

public:

    AdjacencyMatrix(const size_t & verticesNumber, const int* edges);
    AdjacencyMatrix(const AdjacencyMatrix & existingMatrix);
    ~AdjacencyMatrix();

    void print();

    int** getMatrix() const
    {
        return this->matrix;
    }

    int getCost(const size_t & origin, const size_t & destination) const
    {
        return this->matrix[origin][destination];
    }

    size_t getCitiesNumber() const
    {
        return this->citiesNumber;
    }

};