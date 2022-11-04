#include <iostream>
#include <algorithm>
#include <unistd.h>
#include "../inc/containers/AdjacencyMatrix.h"
#include "../inc/utils/FileManager.h"

#define var auto

int main() {
    mkdir("TSP_tests");
    Tests testEntity;
    testEntity.sampleSize = 10;

    testEntity.test();
}