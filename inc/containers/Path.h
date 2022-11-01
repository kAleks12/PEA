//
// Created by kacpe on 21.10.2022.
//

#pragma once

#include <cstdio>
#include "DynamicArray.hpp"

class Path {
private:
    DynamicArray<int>* path;
    int cost;

public:
    Path(const DynamicArray<int> & vertices, int cost);
    Path();
    ~Path();

    void addVertex(int vertex, int vertexCost);
    void addVertex(int vertex);
    void setCost(int totalCost);

    std::string toString();

    int getCost() {
        return cost;
    }
};
