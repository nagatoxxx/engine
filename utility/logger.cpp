#include "logger.h"

/* explicit */ Logger::Logger(std::ostream& stream /* = std::cout */) noexcept
: m_stream(stream)
{
    m_stream << "Logger: created\n";
}

Logger::~Logger() noexcept
{
    m_stream << "Logger: destroyed\n";
}

std::ostream& operator<<(Logger& log, const char* str)
{
    log.m_stream << str << '\n';

    return log.m_stream;
}
