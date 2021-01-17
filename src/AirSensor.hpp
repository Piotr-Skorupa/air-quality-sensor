#pragma once

#include <spdlog/sinks/syslog_sink.h>

#include "PMS.h"
#include "Stream.h"

struct AirData
{
    uint16_t pm_1_0;
    uint16_t pm_2_5;
    uint16_t pm_10_0;
};

class AirSensor
{
public:
    AirSensor(std::shared_ptr<spdlog::logger> logger);

    AirData getData();

private:
    void wakeUpSensor();
    void sleepSensor();

    std::shared_ptr<spdlog::logger> logger;
    Stream stream;
    PMS pmsLib;
};
