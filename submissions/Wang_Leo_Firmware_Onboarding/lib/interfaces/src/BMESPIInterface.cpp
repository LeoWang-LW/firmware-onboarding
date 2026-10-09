#include "BMESPIInterface.h"

bool BMESPIInterface::init()
{
    return _bme.begin();
}

float BMESPIInterface::read_temperature()
{
    _temperature_c = _bme.readTemperature();
    return _temperature_c;
}

float BMESPIInterface::get_temperature() const
{
    return _temperature_c;
}