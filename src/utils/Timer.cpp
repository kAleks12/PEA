//
// Created by kacpe on 21.10.2022.
//

#include "../../inc/utils/Timer.h"
#include <stdexcept>

void Timer::start() {
    startTime = std::chrono::high_resolution_clock::now();
    isStarted = true;
}

double Timer::getTime() {
    if(!isStarted) {
        throw std::runtime_error("Tried to read time before starting timer!");
    }

    endTime = std::chrono::high_resolution_clock::now();
    auto interval =  (std::chrono::duration<double, std::milli> (endTime - startTime)).count();
    isStarted = false;

    return interval;
}

