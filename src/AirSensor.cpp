#include <array>
#include <iostream>

#include "AirSensor.hpp"

constexpr auto PMS_STATUS_OK = 1;

AirSensor::AirSensor(std::shared_ptr<spdlog::logger> logger)
    : logger(std::move(logger))
    , stream{}
    , pmsLib(stream)
{
}

AirData AirSensor::getData() try
{
    PMS::DATA data{};
    wakeUpSensor();

    logger->info("Getting data from sensor.");
    while (pmsLib.read(data) != PMS_STATUS_OK) {}
    logger->info("Data has been verified.");

    sleepSensor();
    return {data.PM_SP_UG_1_0, data.PM_SP_UG_2_5, data.PM_SP_UG_10_0};
}
catch (const std::exception& e)
{
    logger->error("[get data error] -> {0}", e.what());
    return {};
}

void AirSensor::wakeUpSensor() try
{
    logger->info("Sensor is wakeing up. Waiting 30 seconds for stabilization...");
    pmsLib.wakeUp();
    std::this_thread::sleep_for(std::chrono::seconds(30));
    logger->info("Sensor is ready!");
}
catch (const std::exception& e)
{
    logger->error("[set sleep mode error] -> {0}", e.what());
}

void AirSensor::sleepSensor() try
{
    logger->info("Sensor is going into sleep mode until next measuremnt will be requested.");
    pmsLib.sleep();
}
catch (const std::exception& e)
{
    logger->error("[set sleep mode error] -> {0}", e.what());
}