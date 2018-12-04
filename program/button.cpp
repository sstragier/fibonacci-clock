#include "Arduino.h"
#include "button.h"

Button::Button(int pin)
{
    this->pin = pin;

    pinMode(pin, INPUT);
}

bool Button::isOn()
{
    return _isOn;
}

bool Button::hasChanged()
{
    return _hasChanged;
}

// See: http://www.arduino.cc/en/Tutorial/Debounce
void Button::loop()
{
    // read the state of the switch into a local variable:
    int reading = digitalRead(pin);

    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH), and you've waited long enough
    // since the last press to ignore any noise:

    // If the switch changed, due to noise or pressing:
    if (reading != lastButtonState)
    {
        // reset the debouncing timer
        lastDebounceTime = millis();
    }

    _hasChanged = false;

    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        // whatever the reading is at, it's been there for longer than the debounce
        // delay, so take it as the actual current state:

        // if the button state has changed:
        int state = _isOn ? HIGH : LOW;
        if (reading != state)
        {
            _isOn = reading == HIGH;
            _hasChanged = true;
        }
    }

    // save the reading. Next time through the loop, it'll be the lastButtonState:
    lastButtonState = reading;
}