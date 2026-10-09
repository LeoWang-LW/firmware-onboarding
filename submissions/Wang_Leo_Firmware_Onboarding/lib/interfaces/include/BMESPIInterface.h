#pragma once
#include <Adafruit_BME280.h>
#include <etl/singleton.h>
#include "BMEConstants.h"

class BMESPIInterface
{
public:
    BMESPIInterface() = default;

    // Start the sensor. Returns false if it isn't found (wiring/address problem).
    bool init();

    // Read the sensor now, store the result, and return it (°C).
    float read_temperature();

    // Return the last stored reading without touching the hardware.
    float get_temperature() const;

private:
    Adafruit_BME280 _bme{BMEConstants::SPI_CS_PIN};   // the Adafruit driver object (SPI mode)
    float _temperature_c = 0.0f;   // last reading
};

using BMESPIInterfaceInstance = etl::singleton<BMESPIInterface>;