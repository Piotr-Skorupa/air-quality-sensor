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
    PMS::DATA data;
    logger->info("Getting data from sensor.");

    while (pmsLib.read(data) != PMS_STATUS_OK)
    {}

    logger->info("Data has been verified. Returning values.");
    return {data.PM_SP_UG_1_0, data.PM_SP_UG_2_5, data.PM_SP_UG_10_0};
}
catch (const std::exception& e)
{
    logger->error("[get data error] -> {0}", e.what());
    return {};
}
