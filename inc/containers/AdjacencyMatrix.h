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

    int getValue(const size_t & source_, const size_t & destination_) const
    {
        return this->matrix[source_][destination_];
    }

    size_t getCitiesNumber() const
    {
        return this->citiesNumber;
    }

};