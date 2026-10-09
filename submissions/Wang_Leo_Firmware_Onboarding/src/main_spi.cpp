#include <Arduino.h>
#include "BMEConstants.h"
#include "BMESPIInterface.h"
#include "LEDController.h"

// Last time we read the sensor (ms since power-on)
static uint32_t last_read_ms = 0;

void setup()
{
    Serial.begin(115200);   // matches monitor_speed in platformio.ini

    // Create the one-and-only instance of each object
    BMESPIInterfaceInstance::create();
    LEDControllerInstance::create();

    LEDControllerInstance::instance().init();

    // begin() returns false if the sensor didn't answer
    if (!BMESPIInterfaceInstance::instance().init())
    {
        Serial.println("ERROR: BME280 not found over I2C. Check wiring / address.");
        while (true) {}   // stop here forever
    }
    Serial.println("BME280 found over I2C");
}

void loop()
{
    uint32_t now = millis();

    // Read the sensor every SENSOR_READ_MS, without delay()
    if (now - last_read_ms >= BMEConstants::SENSOR_READ_MS)
    {
        last_read_ms = now;

        float temp_c = BMESPIInterfaceInstance::instance().read_temperature();
        LEDControllerInstance::instance().set_temperature(temp_c);

        Serial.print("Temp: ");
        Serial.print(temp_c);
        Serial.print(" C | blink interval: ");
        Serial.print(LEDControllerInstance::instance().get_interval_ms());
        Serial.println(" ms");
    }

    // Runs every loop: flips the LED when enough time has passed
    LEDControllerInstance::instance().update(now);
}