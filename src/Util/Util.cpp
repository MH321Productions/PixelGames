#include "Util.hpp"

using namespace std::chrono;

void Timer::calculateDeltaTime(const bool& startFrame) {
    if (startFrame) {
        start = system_clock::now();
    } else {
        diff = system_clock::now() - start;
        deltaTime = diff.count();
    }
}