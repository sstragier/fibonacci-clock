#include "Arduino.h"

#include "constants.h"
#include "lamp.h"

Lamp::Lamp(Leds* leds)
{
    this->leds = leds;
    invalidate();
}

void Lamp::invalidate()
{
    lastTransitionTime = 0;
    iteration = 0;
}

void Lamp::loop()
{
    for (int i = 0; i < NUM_SQUARES; i++)
    {
        int offset = (i * 255) / NUM_SQUARES;
        int position = (iteration + offset) % 256;
        CRGB color = wheel(position);
        leds->setSquareColor(i, color);
    }

    leds->show();

    if ((millis() - delay) > lastTransitionTime)
    {
        lastTransitionTime = millis();

        // If enough time has passed, increase the iteration for the next loop
        iteration++;
        if (iteration >= 256) iteration = 0;
    }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
CRGB Lamp::wheel(byte position)
{
    if (position < 85)
    {
        return CRGB(position * 3, 255 - position * 3, 0);
    }
    else if (position < 170)
    {
        position -= 85;
        return CRGB(255 - position * 3, 0, position * 3);
    }
    else
    {
        position -= 170;
        return CRGB(0, position * 3, 255 - position * 3);
    }
}