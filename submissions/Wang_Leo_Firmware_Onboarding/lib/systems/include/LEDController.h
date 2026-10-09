#pragma once
#include <Arduino.h>
#include <etl/singleton.h>
#include "BMEConstants.h"

class LEDController
{
public:
    LEDController() = default;

    // Set the LED pin as an output and start with it off.
    void init();

    // Give the controller a new temperature; it recalculates the blink interval.
    void set_temperature(float temp_c);

    // Call every loop(). Flips the LED when enough time has passed.
    void update(uint32_t now_ms);

    uint32_t get_interval_ms() const;

    // Pure math: temperature in, interval out. No hardware involved.
    static uint32_t interval_for_temp(float temp_c);

private:
    uint32_t _interval_ms = BMEConstants::BLINK_SLOW_MS;
    uint32_t _last_toggle_ms = 0;
    bool _led_on = false;
};

using LEDControllerInstance = etl::singleton<LEDController>;