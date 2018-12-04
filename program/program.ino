#include <Arduino.h>

#include "button.h"
#include "clock.h"
#include "constants.h"
#include "lamp.h"
#include "leds.h"

#define NUM_MODES 2

Leds leds;
Clock clock(&leds);
Lamp lamp(&leds);

Button modeButton(MODE_BTN_PIN);
Button colorButton(COLOR_BTN_PIN);
Button minuteButton(MINUTE_BTN_PIN);
Button setButton(SET_BTN_PIN);

int mode = 0;

void setup()
{
    Serial.begin(9600);
    Serial.println("starting");

    leds.begin();
    clock.begin();
}

void loop()
{
    checkButtons();

    if (setButton.isOn())
    {
        // When the set button is held, the color button is used for hours
        if (colorButton.hasChanged() && colorButton.isOn())
        {
            Serial.println("+1 Hour");
            clock.addHours(1);
        }
        else if (minuteButton.hasChanged() && minuteButton.isOn())
        {
            Serial.println("+1 Minute");
            clock.addMinutes(1);
        }
    }
    else if (modeButton.hasChanged() && modeButton.isOn())
    {
        Serial.println("Next mode");
        nextMode();
    }
    else if (colorButton.hasChanged() && colorButton.isOn())
    {
        Serial.println("Next color palette");
        clock.nextPalette();
    }

    switch (mode)
    {
        case 1: lamp.loop(); break;
        default: clock.loop(); break;
    }
}

void checkButtons() {
    modeButton.loop();
    colorButton.loop();
    minuteButton.loop();
    setButton.loop();
}

void nextMode() {
    mode = (mode + 1) % NUM_MODES;

    // Reset the lamp/clock before the loop phase so that they will render correctly
    switch (mode)
    {
        case 1: lamp.invalidate(); break;
        default: clock.invalidate(); break;
    }
}