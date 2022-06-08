#include <iostream>
#include "timer.h"

Timer::Timer(const std::string& message) : message(message), start(std::chrono::steady_clock::now())
{
}

Timer::Timer(const char* message) : Timer(std::string(message))
{
}

Timer::~Timer()
{
    const auto elapsed =
            std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count();
    std::cout << message << ": " << elapsed / 1000.0 << " ms" << std::endl;
}


