#include <iostream>

#include "timer.h"

Timer::Timer() noexcept
{
    std::cout << "Timer: created\n";
}

Timer::~Timer() noexcept
{
    std::cout << "Timer: destroyed\n";
}

void Timer::start() noexcept
{
    m_startTime = m_clock.now();
}

float Timer::reset() noexcept
{
    m_endTime = m_clock.now();

    std::chrono::duration<float> elapsed_time = m_endTime - m_startTime;

    m_startTime = m_clock.now();

    return elapsed_time.count();
}

float Timer::getElapsedTime() noexcept
{
    m_endTime = m_clock.now();

    std::chrono::duration<float> elapsed_time = m_endTime - m_startTime;

    return elapsed_time.count();
}
