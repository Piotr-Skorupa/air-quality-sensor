#include "Timer.hpp"

Timer::Timer()
    : isRunning_(false)
    {}

bool Timer::isRunning() const
{
    return isRunning_;
}

void Timer::start()
{
    startTimer_ = std::chrono::high_resolution_clock::now();
    isRunning_ = true;
}

void Timer::stop()
{
    endTimer_ = std::chrono::high_resolution_clock::now();
}

void Timer::stopRunning()
{
    isRunning_ = false;
    stop();
}

int Timer::getSeconds()
{
    using namespace std::chrono;
    stop();
    duration<double> timeSpan = duration_cast<duration<double>>(endTimer_ - startTimer_);
    return static_cast<int>(timeSpan.count());
}

int Timer::getMinutes()
{
    return getSeconds() / 60;
}

bool Timer::isPeriodFinished(const std::chrono::seconds& period)
{
    return getSeconds() % period.count() == 0;
}
