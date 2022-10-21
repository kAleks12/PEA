#include "DynamicArray.tpp"
#include "../../inc/containers/Path.h"


//
// Created by kacpe on 21.10.2022.
//
Path::Path(const DynamicArray<int> &vertices, int cost) : path(vertices), cost(cost) {}
Path::Path() {
    cost = 0;
}

void Path::addVertex(int vertex, int vertexCost) {
    path.addBack(vertex);
    cost += vertexCost;
}

void Path::setCost(int totalCost) {
    this->cost = totalCost;
}

std::string Path::toString() {
    std::string path_str;

    for(int iterator = 0; iterator < path.getSize(); iterator ++) {
        auto vertex_str = std::to_string(path.at(iterator));

        path_str.append(vertex_str)
                .append(" -> ");
    }
    path_str.append("\nTotal cost: ")
            .append(std::to_string(cost));

    return path_str;
}
