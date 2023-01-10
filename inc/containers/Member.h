//
// Created by kacpe on 27.12.2022.
//

#pragma once

#include <iostream>
#include "DynamicArray.hpp"

class Member {
public:
    Member() = default;
    Member(LiteDynamicArray<size_t> &path, int cost) : path(path), cost(cost) {};

    bool operator<(const Member &other) const {
        return cost < other.cost;
    }

    bool operator !=(const Member &other) {
        return !(this->path == other.path);
    }

    bool operator ==(const Member &other) {
        return this->path == other.path;
    }

    void setPath(LiteDynamicArray<size_t> newPath) {
        path = newPath;
    }

    LiteDynamicArray<size_t> path;
    int cost{INT_MAX};
};