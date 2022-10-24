//
// Created by kacpe on 21.10.2022.
//

#include "../../inc/utils/Timer.h"
#include <stdexcept>

void Timer::start() {
    startTime = std::chrono::high_resolution_clock::now();
    isStarted = true;
}

double Timer::getTime(TimeUnit unit) {
    if(!isStarted) {
        throw std::runtime_error("Tried to read time before starting timer!");
    }

    endTime = std::chrono::high_resolution_clock::now();
    isStarted = false;

    switch(unit) {
        case NANOSECONDS:
            return  (std::chrono::duration<double, std::nano> (endTime - startTime)).count();
            break;

        case MICROSECONDS:
            return  (std::chrono::duration<double, std::micro> (endTime - startTime)).count();
            break;

        case MILLISECONDS:
            return  (std::chrono::duration<double, std::milli> (endTime - startTime)).count();
            break;

        default:
            throw std::runtime_error("Tried using unsupported time unit!");
    }

}

