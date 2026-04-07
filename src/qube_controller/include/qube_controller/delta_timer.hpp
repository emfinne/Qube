
#ifndef BUILD_DELTA_TIMER_HPP
#define BUILD_DELTA_TIMER_HPP

#include <chrono>
#include <algorithm>

class delta_timer {
public:
    double step() {
        auto now = clock::now();
        double deltaTime = std::chrono::duration<double>(now - last_).count();
        last_ = now;
        return deltaTime;
    }
    double step(double min, double max)
    {
        auto now = clock::now();
        double deltaTime = std::chrono::duration<double>(now - last_).count();
        last_ = now;
        return std::clamp(deltaTime, min, max);
    }

private:
    using clock = std::chrono::steady_clock;
    clock::time_point last_ = clock::now();
};

#endif //BUILD_DELTA_TIMER_HPP
