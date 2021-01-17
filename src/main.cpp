#include <cstdlib>
#include <chrono>
#include <csignal>
#include <thread>
#include <string>

#include <spdlog/sinks/syslog_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "AirSensor.hpp"
#include "config.hpp"
#include "Timer.hpp"
#include "WebClient.hpp"

constexpr auto APPLICATION_NAME = "AQS-SERVICE";

static int signalNumber = 0;
static bool isRunning = true;

void signalHandler(int sigNum)
{
    signalNumber = sigNum;
    isRunning = false;
}

int main()
{
    auto logger = spdlog::syslog_logger_mt("syslog", APPLICATION_NAME, LOG_PID);
    //auto logger = spdlog::stdout_color_mt(APPLICATION_NAME); // DEBUG stdout logger

    logger->info("**** Starting <AIR QUALITY SENSOR SERVICE> ****");

    std::signal(SIGTERM, signalHandler);
    std::signal(SIGINT, signalHandler);

    WebClient webClient(logger, std::make_unique<signomix::HttpClient>(signomix::initializeCurl()));
    AirSensor airSensor(logger);
    Timer timer;
    timer.start();

    uint measurementCounter = 0;
    while(isRunning)
    {
        if(timer.isPeriodFinished(std::chrono::seconds(MEASUREMENT_PERIOD_SEC)))
        {
            logger->info("{0}. Checking air quality...", ++measurementCounter);
            auto data = airSensor.getData();
            logger->info("AIR QUALITY:");
            logger->info("PM 1.0: {0}", data.pm_1_0);
            logger->info("PM 2.5: {0}", data.pm_2_5);
            logger->info("PM 10.0: {0}", data.pm_10_0);
            webClient.sendData("air_quality", data.pm_10_0);
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    logger->info("Catched signal {0} !!!", signalNumber);
    logger->info("**** Closing <AIR QUALITY SENSOR SERVICE> ****");
    return signalNumber;
}
