#include "Stream.h"

constexpr auto PMS7003_PORT = "/dev/ttyS0";

Stream::Stream()
    : io{}
    , serial(io, PMS7003_PORT)
{
    serial.set_option(boost::asio::serial_port_base::baud_rate(9600));
}

Stream::~Stream()
{
    if (serial.is_open())
    {
        serial.close();
    }
}

bool Stream::available()
{
    return true;
}

void Stream::write(uint8_t* command, int size)
{
    // not implemented
}

uint8_t Stream::read()
{
    if (not serial.is_open())
    {
        return {};
    }

    uint8_t byte{};
    boost::asio::read(serial,boost::asio::buffer(&byte,1));

    return byte;
}