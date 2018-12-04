#ifndef _CLOCK_LAMP_H_
#define _CLOCK_LAMP_H_

#include "Arduino.h";
#include "FastLED.h"

#include "leds.h"

class Lamp
{
private:
    Leds* leds;
    unsigned long lastTransitionTime = 0;
    unsigned int iteration = 0;

    CRGB wheel(byte position);

public:
    int delay = 20;

    Lamp(Leds* leds);
    void loop();
    void invalidate();
};

#endif // _CLOCK_LAMP_H_