#pragma once 
#include <Arduino.h> 

namespace BMEConstants
{
    //Sensor connection 
    constexpr uint8_t I2C_ADDRESS = 0x77;
    constexpr uint8_t SPI_CS_PIN = 10;

    //LED
    constexpr uint8_t LED_PIN = 9;

    //Temperature range the LED responds to (C)
    constexpr float TEMP_MIN_C = 20.0f;
    constexpr float TEMP_MAX_C = 35.0f; 

    //Blink interval (ms) | Slow when cold, fast when hot 
    constexpr uint32_t BLINK_SLOW_MS = 1000; 
    constexpr uint32_t BLINK_FAST_MS = 100;

    // How often to read the sensor (ms)
    constexpr uint32_t SENSOR_READ_MS = 500;
}