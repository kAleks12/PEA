//
// Created by kacpe on 10.01.2023.
//

#pragma once

#include "../../containers/LiteDynamicArray.h"
#include "../../../src/containers/LiteDynamicArray.tpp"

class GeneticHelper {
public:
    static void swapMutation(LiteDynamicArray <size_t> &path);

    static void insertMutation(LiteDynamicArray <size_t> &path);

    static void invertMutation(LiteDynamicArray <size_t> &path);

    static void scrambleMutation(LiteDynamicArray <size_t> &path);

    static LiteDynamicArray <size_t> OXCrossover(
            LiteDynamicArray <size_t> &firstParent, LiteDynamicArray <size_t> &secondParent);
};
