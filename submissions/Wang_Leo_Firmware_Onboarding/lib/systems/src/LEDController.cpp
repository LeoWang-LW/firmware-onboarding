#include "LEDController.h"

void LEDController::init()
{
    pinMode(BMEConstants::LED_PIN, OUTPUT);
    digitalWrite(BMEConstants::LED_PIN, LOW);
}

uint32_t LEDController::interval_for_temp(float temp_c)
{
    // If the sensor read failed, it returns NaN ("not a number"). Fall back to slow.
    if (isnan(temp_c))
    {
        return BMEConstants::BLINK_SLOW_MS;
    }

    float fraction = (temp_c - BMEConstants::TEMP_MIN_C) /
                     (BMEConstants::TEMP_MAX_C - BMEConstants::TEMP_MIN_C);
    fraction = constrain(fraction, 0.0f, 1.0f);   // clamp to 0..1

    float range = BMEConstants::BLINK_SLOW_MS - BMEConstants::BLINK_FAST_MS;
    return BMEConstants::BLINK_SLOW_MS - (uint32_t)(fraction * range);
}

void LEDController::set_temperature(float temp_c)
{
    _interval_ms = interval_for_temp(temp_c);
}

void LEDController::update(uint32_t now_ms)
{
    if (now_ms - _last_toggle_ms >= _interval_ms)
    {
        _last_toggle_ms = now_ms;
        _led_on = !_led_on;
        digitalWrite(BMEConstants::LED_PIN, _led_on ? HIGH : LOW);
    }
}

uint32_t LEDController::get_interval_ms() const
{
    return _interval_ms;
}