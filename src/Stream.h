#pragma once

#include <boost/asio/serial_port.hpp>
#include <boost/asio.hpp>

class Stream
{
public:
    Stream();
    ~Stream();
    bool available();
    void write(uint8_t* command, int size);
    uint8_t read();

private:
    boost::asio::io_service io;
    boost::asio::serial_port serial;
};
