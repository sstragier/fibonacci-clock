#ifndef _CLOCK_LEDS_H_
#define _CLOCK_LEDS_H_

#include "Arduino.h"
#include "FastLED.h"
#include "constants.h"

class Leds
{
private:
    CRGB leds[NUM_LEDS];

public:
    void begin();
    void setSquareColor(int squareIndex, CRGB color);
    void show();
};

#endif // _CLOCK_LEDS_H_