#pragma once

#include <memory>
#include <string>

#include <signomix.hpp>
#include <spdlog/sinks/syslog_sink.h>

class WebClient
{
public:
    WebClient(std::shared_ptr<spdlog::logger> logger, std::unique_ptr<signomix::HttpClient> client);

    void sendData(const std::string& field, int data);

private:
    bool signomixConnect();

    std::shared_ptr<spdlog::logger> logger;
    std::unique_ptr<signomix::HttpClient> client;
    bool isConnected;
};
