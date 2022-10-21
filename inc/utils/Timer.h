//
// Created by kacpe on 21.10.2022.
//

#pragma once

#include <chrono>

class clock;

class Timer {
private:
        bool isStarted = false;
        std::chrono::high_resolution_clock::time_point startTime;
        std::chrono::high_resolution_clock::time_point endTime;

public:
    void start();
    double getTime();
};
