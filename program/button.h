#ifndef _CLOCK_BUTTON_H_
#define _CLOCK_BUTTON_H_

#include "Arduino.h"

class Button {
private:
    int pin;
    bool _isOn = false;
    bool _hasChanged = false;
    int lastButtonState = LOW;
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 50;

public:
    Button(int pin);
    void loop();

    bool isOn();
    bool hasChanged();
};

#endif // _CLOCK_BUTTON_H_