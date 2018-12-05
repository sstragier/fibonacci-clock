#ifndef _CLOCK_LAMP_H_
#define _CLOCK_LAMP_H_

#include "Arduino.h"
#include "FastLED.h"

#include "leds.h"

#define NUM_LAMP_SPEEDS 4

class Lamp
{
private:
    Leds* leds;
    // The number of milliseconds between each color transition
    int speeds[NUM_LAMP_SPEEDS] = {20, 40, 80, 100};
    unsigned long lastTransitionTime = 0;
    unsigned int iteration = 0;
    int speedIndex = 0;

    CRGB wheel(byte position);

public:
    Lamp(Leds* leds);
    void loop();
    void nextSpeed();
    int getSpeed();
    void setSpeed(int index);
    void invalidate();
};

#endif // _CLOCK_LAMP_H_