//
// Created by kacpe on 27.12.2022.
//

#pragma once

#include <iostream>
#include "DynamicArray.hpp"

class Member {
public:
    Member() = default;
    Member(DynamicArray<int> &path, int cost) : path(path), cost(cost) {};

    bool operator<(const Member &other) const {
        return cost < other.cost;
    }

    bool operator !=(const Member &other) {
        return !(this->path == other.path);
    }

    bool operator ==(const Member &other) {
        return this->path == other.path;
    }


//    friend std::ostream& operator<<(std::ostream& os, const Member& dt);

    int getCost() const {
        return cost;
    }

    DynamicArray<int> getPath() const {
        return path;
    }

    void setPath(DynamicArray<int> newPath) {
        path = newPath;
    }

private:
    DynamicArray<int> path;
    int cost{INT_MAX};
};

//std::ostream& operator<<(std::ostream& os, const Member& dt)
//{
//    os << dt.getPath().toString();
//    return os;
//}