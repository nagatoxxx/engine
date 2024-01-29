#pragma once

#include <iostream>
#include <ostream>

class Logger
{
    friend std::ostream& operator<<(Logger& log, const char* str);

public:
    explicit Logger(std::ostream& stream = std::cout) noexcept;
    ~Logger() noexcept;

private:
    std::ostream& m_stream;
};
