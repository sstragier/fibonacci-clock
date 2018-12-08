#ifndef _CLOCK_LDR_H_
#define _CLOCK_LDR_H_

#include "constants.h"

class Ldr
{
private:
    int pin;
    int brightness = MAX_BRIGHTNESS;
    bool changed = false;
    int debounceDelay = 1000;
    unsigned long lastDebounceTime = 0;
    int lastReading = 0;

public:
    Ldr(int pin);
    void loop();
    int getBrightness();
    boolean hasChanged();
};

#endif // _CLOCK_LDR_H_