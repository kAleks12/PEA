//
// Created by kacpe on 21.10.2022.
//

#pragma once

#include "../containers/AdjacencyMatrix.h"
#include "../containers/DynamicArray.hpp"
#include "../containers/Path.h"

class Algorithm {
    virtual Path* execute(AdjacencyMatrix &graph, int initialVertex) = 0;
    virtual void testExecute(AdjacencyMatrix &graph, int initialVertex) = 0;
};
