#include <Arduino.h>
#include <RTClib.h>
#include "FastLED.h"
#include <Wire.h>

#include "colors.h"

#define NUM_LEDS 10
#define NUM_CLOCK_SQUARES 5
#define FLAG_HOUR_ON 0x01
#define FLAG_MINUTE_ON 0x02
#define DEBOUNCE_DELAY 10
#define MAX_BUTTONS_INPUT 20

#define LED_PIN 8
#define BUTTON_PIN 4
#define SET_PIN 5
#define HOUR_PIN 6
#define MINUTE_PIN 7

// The LED strip
CRGB leds[NUM_LEDS];
RTC_DS3231 rtc;
byte clockSquares[NUM_CLOCK_SQUARES];

int prevHour = 9999;
int prevMinute = 9999;
int prevButtonValue[MAX_BUTTONS_INPUT];
int currentButtonValue[MAX_BUTTONS_INPUT];

void setup()
{
    Serial.begin(9600);
    Serial.println("starting");

    setupLeds();
    setupClock();
    setupButtons();
}

void setupLeds()
{
    FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
}

void setupButtons()
{
    pinMode(BUTTON_PIN, INPUT);
    pinMode(SET_PIN, INPUT);
    pinMode(HOUR_PIN, INPUT);
    pinMode(MINUTE_PIN, INPUT);
}

void setupClock()
{
    Wire.begin();
    rtc.begin();

    if (rtc.lostPower())
    {
        Serial.println("RTC lost power, lets set the time!");
        //setTime(DateTime(F(__DATE__), F(__TIME__)));
    }
}

void loop()
{

    int hour_button = debounce(HOUR_PIN);
    int minute_button = debounce(MINUTE_PIN);

    DateTime now = rtc.now();

    if (hour_button && hasChanged(HOUR_PIN))
    {
        setTime(DateTime(now.unixtime() + 3600));
    }
    else if (minute_button && hasChanged(MINUTE_PIN))
    {
        // Only increase the minutes, don't also increase the hours
        setTime(DateTime(now.year(), now.month(), now.day(), now.hour(), (now.minute() + 1) % 60));
    }

    resetButtonValues();

    int hour = now.hour();
    if (hour > 12)
        hour %= 12;
    int minute = now.minute() / 5;

    if (hour == prevHour && minute == prevMinute)
        return;
    printDateTime(now);
    Serial.print("Hour: ");
    Serial.print(hour, DEC);
    Serial.print(" Minute: ");
    Serial.print(minute, DEC);
    Serial.println();

    prevHour = hour;
    prevMinute = minute;

    resetClockSquareFlags();
    setClockSquareFlags(hour, FLAG_HOUR_ON);
    setClockSquareFlags(minute, FLAG_MINUTE_ON);

    for (int i = 0; i < NUM_CLOCK_SQUARES; i++)
    {
        updateLed(i, clockSquares[i]);
    }
    FastLED.show();
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

void resetClockSquareFlags()
{
    for (int i = 0; i < NUM_CLOCK_SQUARES; i++)
    {
        clockSquares[i] = 0;
    }
}

void setClockSquareFlags(byte value, byte flag)
{
    switch (value)
    {
    case 1:
        switch (random(2))
        {
        case 0:
            clockSquares[0] |= flag;
            break;
        case 1:
            clockSquares[1] |= flag;
            break;
        }
        break;
    case 2:
        switch (random(2))
        {
        case 0:
            clockSquares[2] |= flag;
            break;
        case 1:
            clockSquares[0] |= flag;
            clockSquares[1] |= flag;
            break;
        }
        break;
    case 3:
        switch (random(3))
        {
        case 0:
            clockSquares[3] |= flag;
            break;
        case 1:
            clockSquares[0] |= flag;
            clockSquares[2] |= flag;
            break;
        case 2:
            clockSquares[1] |= flag;
            clockSquares[2] |= flag;
            break;
        }
        break;
    case 4:
        switch (random(3))
        {
        case 0:
            clockSquares[0] |= flag;
            clockSquares[3] |= flag;
            break;
        case 1:
            clockSquares[1] |= flag;
            clockSquares[3] |= flag;
            break;
        case 2:
            clockSquares[0] |= flag;
            clockSquares[1] |= flag;
            clockSquares[2] |= flag;
            break;
        }
        break;
    case 5:
        switch (random(3))
        {
        case 0:
            clockSquares[4] |= flag;
            break;
        case 1:
            clockSquares[2] |= flag;
            clockSquares[3] |= flag;
            break;
        case 2:
            clockSquares[0] |= flag;
            clockSquares[1] |= flag;
            clockSquares[3] |= flag;
            break;
        }
        break;
    case 6:
        switch (random(4))
        {
        case 0:
            clockSquares[0] |= flag;
            clockSquares[4] |= flag;
            break;
        case 1:
            clockSquares[1] |= flag;
            clockSquares[4] |= flag;
            break;
        case 2:
            clockSquares[0] |= flag;
            clockSquares[2] |= flag;
            clockSquares[3] |= flag;
            break;
        case 3:
            clockSquares[1] |= flag;
            clockSquares[2] |= flag;
            clockSquares[3] |= flag;
            break;
        }
        break;
    case 7:
        switch (random(3))
        {
        case 0:
            clockSquares[2] |= flag;
            clockSquares[4] |= flag;
            break;
        case 1:
            clockSquares[0] |= flag;
            clockSquares[1] |= flag;
            clockSquares[4] |= flag;
            break;
        case 2:
            clockSquares[0] |= flag;
            clockSquares[1] |= flag;
            clockSquares[2] |= flag;
            clockSquares[3] |= flag;
            break;
        }
        break;
    case 8:
        switch (random(3))
        {
        case 0:
            clockSquares[3] |= flag;
            clockSquares[4] |= flag;
            break;
        case 1:
            clockSquares[0] |= flag;
            clockSquares[2] |= flag;
            clockSquares[4] |= flag;
            break;
        case 2:
            clockSquares[1] |= flag;
            clockSquares[2] |= flag;
            clockSquares[4] |= flag;
            break;
        }
        break;
    case 9:
        switch (random(3))
        {
        case 0:
            clockSquares[0] |= flag;
            clockSquares[3] |= flag;
            clockSquares[4] |= flag;
            break;
        case 1:
            clockSquares[1] |= flag;
            clockSquares[3] |= flag;
            clockSquares[4] |= flag;
            break;
        case 2:
            clockSquares[0] |= flag;
            clockSquares[1] |= flag;
            clockSquares[2] |= flag;
            clockSquares[4] |= flag;
            break;
        }
        break;
    case 10:
        switch (random(2))
        {
        case 0:
            clockSquares[2] |= flag;
            clockSquares[3] |= flag;
            clockSquares[4] |= flag;
            break;
        case 1:
            clockSquares[0] |= flag;
            clockSquares[1] |= flag;
            clockSquares[3] |= flag;
            clockSquares[4] |= flag;
            break;
        }
        break;
    case 11:
        switch (random(2))
        {
        case 0:
            clockSquares[0] |= flag;
            clockSquares[2] |= flag;
            clockSquares[3] |= flag;
            clockSquares[4] |= flag;
            break;
        case 1:
            clockSquares[1] |= flag;
            clockSquares[2] |= flag;
            clockSquares[3] |= flag;
            clockSquares[4] |= flag;
            break;
        }
        break;
    case 12:
        clockSquares[0] |= flag;
        clockSquares[1] |= flag;
        clockSquares[2] |= flag;
        clockSquares[3] |= flag;
        clockSquares[4] |= flag;
        break;
    }
}

void updateLed(int squareIndex, byte flags)
{
    CRGB color = colors[0][flags];

    Serial.print("Updating LED ");
    Serial.print(squareIndex, DEC);
    Serial.print("with flag: ");
    Serial.println(flags, DEC);

    switch (squareIndex)
    {
    case 0:
        leds[9] = color;
        break;
    case 1:
        leds[8] = color;
        break;
    case 2:
        leds[7] = color;
        break;
    case 3:
        leds[6] = leds[5] = color;
        break;
    case 4:
        leds[4] = leds[3] = leds[2] = leds[1] = leds[0] = color;
        break;
    }
}

void setTime(DateTime now)
{
    rtc.adjust(now);

    Serial.print("setting time to: ");
    printDateTime(now);
}

void printDateTime(DateTime now)
{
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
}
