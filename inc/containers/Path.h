//
// Created by kacpe on 21.10.2022.
//

#pragma once

#include <cstdio>
#include "DynamicArray.hpp"

class Path {
    DynamicArray<int> path;
    int cost;

public:
    Path(const DynamicArray<int> &vertices, int cost);
    Path();

    void addVertex(int vertex, int vertexCost);
    void setCost(int totalCost);

    std::string toString();
};
