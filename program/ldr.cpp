#include "ldr.h"

Ldr::Ldr(int pin)
{
    this->pin = pin;

    pinMode(pin, INPUT);
}

int Ldr::getBrightness()
{
    return brightness;
}

boolean Ldr::hasChanged()
{
    return changed;
}

void Ldr::loop()
{
    int reading = analogRead(pin);
    reading = constrain(reading, 0, LDR_MAX);
    reading = map(reading, 0, LDR_MAX, 1, MAX_BRIGHTNESS);

    // If the light dependent resistor changed, due to noise or a shadow passing over:
    if (reading != lastReading)
    {
        // reset the debouncing timer
        lastDebounceTime = millis();
    }

    changed = false;

    // Capture the reading if it has been the same for the duration of the debounce delay
    if (lastDebounceTime == 0 || (millis() - lastDebounceTime) > debounceDelay)
    {
        if (reading != brightness)
        {
            brightness = reading;
            changed = true;
        }
    }

    // Save the reading so it can be checked for changes
    lastReading = reading;
}