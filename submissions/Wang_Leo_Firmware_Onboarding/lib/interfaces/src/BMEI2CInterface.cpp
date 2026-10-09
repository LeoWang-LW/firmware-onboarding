#include "BMEI2CInterface.h"

bool BMEI2CInterface::init()
{
    return _bme.begin(BMEConstants::I2C_ADDRESS);
}

float BMEI2CInterface::read_temperature()
{
    _temperature_c = _bme.readTemperature();
    return _temperature_c;
}

float BMEI2CInterface::get_temperature() const
{
    return _temperature_c;
}