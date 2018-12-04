#include <Arduino.h>
#include <EEPROM.h>

#include "button.h"
#include "clock.h"
#include "constants.h"
#include "lamp.h"
#include "leds.h"

#define MODE_CLOCK 0
#define MODE_LAMP 1

Leds leds;
Clock clock(&leds);
Lamp lamp(&leds);

Button modeButton(MODE_BTN_PIN);
Button colorButton(COLOR_BTN_PIN);
Button offButton(OFF_BTN_PIN);
Button setButton(SET_BTN_PIN);

bool isOn = true;
int mode = 0;

void setup()
{
    Serial.begin(9600);
    Serial.println("starting");

    leds.begin();
    clock.begin();

    loadSettings();
    // If the settings have the clock turned off, don't turn it on
    if (!isOn) turnOff();
}

void loop()
{
    checkButtons();

    // Only check for the on/off button when the clock is off (ignore all other buttons)
    if (!isOn)
    {
        if (offButton.hasChanged() && offButton.isOn())
        {
            Serial.println("Turning on");
            turnOn();
        }
    }
    else if (setButton.isOn())
    {
        // When the set button is held, the color button is used for hours and the off button is used for minutes
        if (mode == MODE_CLOCK && colorButton.hasChanged() && colorButton.isOn())
        {
            Serial.println("+1 Hour");
            clock.addHours(1);
        }
        else if (mode == MODE_CLOCK && offButton.hasChanged() && offButton.isOn())
        {
            Serial.println("+1 Minute");
            clock.addMinutes(1);
        }
    }
    else if (offButton.hasChanged() && offButton.isOn())
    {
        Serial.println("Turning off");
        turnOff();
    }
    else if (modeButton.hasChanged() && modeButton.isOn())
    {
        Serial.println("Next mode");
        nextMode();
    }
    else if (mode == MODE_CLOCK && colorButton.hasChanged() && colorButton.isOn())
    {
        Serial.println("Next color palette");
        clock.nextPalette();
        saveSettings();
    }

    if (!isOn) return;

    switch (mode)
    {
        case MODE_LAMP: lamp.loop(); break;
        default: clock.loop(); break;
    }
}

void checkButtons() {
    modeButton.loop();
    colorButton.loop();
    offButton.loop();
    setButton.loop();
}

void turnOn() {
    isOn = true;
    saveSettings();

    // Make sure that the clock/lamp immediately re-render
    clock.invalidate();
    lamp.invalidate();
}

void turnOff() {
    isOn = false;
    saveSettings();

    leds.off();
}

void nextMode() {
    // Set the mode and then invalidate the model so that it renders correctly
    switch (mode)
    {
        case MODE_CLOCK:
            mode = MODE_LAMP;
            lamp.invalidate();
            break;
        default:
            mode = MODE_CLOCK;
            clock.invalidate();
            break;
    }
    
    saveSettings();
}

void loadSettings()
{
    // FYI uninitialized EEPROM values default to 255
    byte value = EEPROM.read(0);
    if (value == MODE_CLOCK || value == MODE_LAMP) mode = value;

    isOn = EEPROM.read(1) != 0;
    clock.setPalette(EEPROM.read(2));

    Serial.print("Loaded mode: ");
    Serial.print(mode, DEC);
    Serial.println(mode == MODE_LAMP ? " (Lamp)" : " (Clock)");

    Serial.print("Loaded on/off: ");
    Serial.println(isOn ? "on" : "off");

    Serial.print("Loaded color palette: ");
    Serial.println(clock.getPalette());
}

void saveSettings()
{
    EEPROM.write(0, mode);
    EEPROM.write(1, (byte)isOn);
    EEPROM.write(2, clock.getPalette());
}