#pragma once

#include <chrono>
#include <string>

class Timer
{
public:
    Timer();
    bool isRunning() const;
    void start();
    void stop();
    void stopRunning();
    int getSeconds();
    int getMinutes();
    bool isPeriodFinished(const std::chrono::seconds& period);

private:
    std::chrono::high_resolution_clock::time_point startTimer_;
    std::chrono::high_resolution_clock::time_point endTimer_;

    bool isRunning_;
};
