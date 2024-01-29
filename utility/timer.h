#pragma once

#include <chrono>

class Timer
{
public:
    Timer() noexcept;
    ~Timer() noexcept;

    void start() noexcept;

    float reset() noexcept; // returns elapsed time in seconds and resets timer
    [[nodiscard]] float getElapsedTime() noexcept;

private:
    std::chrono::high_resolution_clock             m_clock;
    std::chrono::high_resolution_clock::time_point m_startTime;
    std::chrono::high_resolution_clock::time_point m_endTime;
};
