#include <Arduino.h>

#include "clock.h"
#include "constants.h"

#define DEBOUNCE_DELAY 10
#define MAX_BUTTONS_INPUT 20

#define BUTTON_PIN 4
#define SET_PIN 5
#define HOUR_PIN 6
#define MINUTE_PIN 7

Clock clock;

int prevButtonValue[MAX_BUTTONS_INPUT];
int currentButtonValue[MAX_BUTTONS_INPUT];

void setup()
{
    Serial.begin(9600);
    Serial.println("starting");
    clock.begin();
    setupButtons();
}

void setupButtons()
{
    pinMode(BUTTON_PIN, INPUT);
    pinMode(SET_PIN, INPUT);
    pinMode(HOUR_PIN, INPUT);
    pinMode(MINUTE_PIN, INPUT);
}

void loop()
{
    int hour_button = debounce(HOUR_PIN);
    int minute_button = debounce(MINUTE_PIN);

    clock.loop();

    /*DateTime now = rtc.now();

    if (hour_button && hasChanged(HOUR_PIN))
    {
        setTime(DateTime(now.unixtime() + 3600));
    }
    else if (minute_button && hasChanged(MINUTE_PIN))
    {
        // Only increase the minutes, don't also increase the hours
        setTime(DateTime(now.year(), now.month(), now.day(), now.hour(), (now.minute() + 1) % 60));
    }*/

    //resetButtonValues();
}

int debounce(int pin)
{
    int val = digitalRead(pin);
    if (val == prevButtonValue[pin])
    {
        currentButtonValue[pin] = val;
        return val;
    }

    delay(DEBOUNCE_DELAY);

    val = digitalRead(pin);
    if (val != prevButtonValue[pin])
    {
        Serial.print(pin, DEC);
        Serial.print(" is ");
        Serial.println(val, DEC);
        currentButtonValue[pin] = val;
        return val;
    }

    currentButtonValue[pin] = prevButtonValue[pin];
    return prevButtonValue[pin];
}

boolean hasChanged(int pin)
{
    return prevButtonValue[pin] != currentButtonValue[pin];
}

void resetButtonValues()
{
    for (int i = 0; i < MAX_BUTTONS_INPUT; i++)
    {
        prevButtonValue[i] = currentButtonValue[i];
    }
}