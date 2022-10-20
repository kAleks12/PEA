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

    void initialize(const int* data_);
    void copy(int** dataFromOrigin_);

public:

    AdjacencyMatrix(const size_t & citiesNumber_, const int* data_);
    AdjacencyMatrix(const AdjacencyMatrix & origin_);
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