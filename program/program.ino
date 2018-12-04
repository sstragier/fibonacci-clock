#include <Arduino.h>

#include "button.h"
#include "clock.h"
#include "constants.h"

Clock clock;
Button setButton(SET_BTN_PIN);
Button colorButton(COLOR_BTN_PIN);
Button minuteButton(MINUTE_BTN_PIN);

void setup()
{
    Serial.begin(9600);
    Serial.println("starting");

    clock.begin();
}

void loop()
{
    checkButtons();

    if (setButton.isOn()) {
        // When the set button is held, the color button is used for hours
        if (colorButton.hasChanged() && colorButton.isOn()) {
            Serial.println("+1 Hour");
            clock.addHours(1);
        } else if (minuteButton.hasChanged() && minuteButton.isOn()) {
            Serial.println("+1 Minute");
            clock.addMinutes(1);
        }
    } else if (colorButton.hasChanged() && colorButton.isOn()) {
        Serial.println("Next color palette");
        clock.nextPalette();
    }

    clock.loop();
}

void checkButtons() {
    setButton.loop();
    colorButton.loop();
    minuteButton.loop();
}