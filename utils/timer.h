#pragma once

#include <string>
#include <chrono>

class Timer
{
public:
    Timer(const char* message);
    Timer(const std::string& message);
    Timer(Timer&) = delete;
    ~Timer();

    Timer& operator=(Timer&) = delete;

private:
    std::string message;
    std::chrono::time_point<std::chrono::steady_clock> start;
};