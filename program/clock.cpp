#include "Arduino.h"
#include "clock.h"
#include "colors.h"
#include "constants.h"

Clock::Clock() {
}

void Clock::begin() {
    Serial.println("Clock constructor");
    Wire.begin();
    Serial.println("started Wire");
    rtc.begin();
    Serial.println("started RTC");

    if (rtc.lostPower()) {
        Serial.println("RTC lost power, lets set the time!");
        setTime(DateTime(F(__DATE__), F(__TIME__)));
    }
    else {
        Serial.print("Resuming clock @ ");
        printTime(getTime());
    }

    FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
}

void Clock::loop() {
    DateTime now = getTime();
    
    int hour = now.hour();
    int minute = now.minute();
    
    if (hour == prevHour && minute == prevMinute) return;

    displayTime(hour, minute);

    prevHour = hour;
    prevMinute = minute;
}

void Clock::displayTime(int hour, int minute) {
    if (hour > 12) hour %= 12;
    minute /= 5;

    resetSquareFlags();
    setSquareFlags(hour, FLAG_HOUR_ON);
    setSquareFlags(minute, FLAG_MINUTE_ON);
    updateLeds();
}

void Clock::resetSquareFlags() {
    for (int i = 0; i < NUM_SQUARES; i++) {
        squareFlags[i] = 0;
    }
}

void Clock::updateLeds() {
    for (int i = 0; i < NUM_SQUARES; i++) {
        updateLed(i, squareFlags[i]);
    }

    FastLED.show();
}

void Clock::updateLed(int squareIndex, byte flags) {
    CRGB color = colors[0][flags];

    switch (squareIndex) {
        case 0: leds[9] = color; break;
        case 1: leds[8] = color; break;
        case 2: leds[7] = color; break;
        case 3: leds[5] = leds[6] = color; break;
        case 4: leds[0] = leds[1] = leds[2] = leds[3] = leds[4] = color; break;
    }
}

DateTime Clock::getTime() {
    return rtc.now();
}

void Clock::setTime(DateTime now) {
    Serial.print("setting time to: "); printTime(now);
    
    rtc.adjust(now);
}

void Clock::setSquareFlags(int value, byte flag) {
    switch (value) {
        case 1:
            switch (random(2))
            {
                case 0: setSquareFlags(flag, 1, 0, 0, 0, 0); break;
                case 1: setSquareFlags(flag, 0, 1, 0, 0, 0); break;
            }
            break;
        case 2:
            switch (random(2))
            {
                case 0: setSquareFlags(flag, 1, 1, 0, 0, 0); break;
                case 1: setSquareFlags(flag, 0, 0, 1, 0, 0); break;
            }
            break;
        case 3:
            switch (random(3))
            {
                case 0: setSquareFlags(flag, 1, 0, 1, 0, 0); break;
                case 1: setSquareFlags(flag, 0, 1, 1, 0, 0); break;
                case 2: setSquareFlags(flag, 0, 0, 0, 1, 0); break;
            }
            break;
        case 4:
            switch (random(3))
            {
                case 0: setSquareFlags(flag, 1, 1, 1, 0, 0); break;
                case 1: setSquareFlags(flag, 1, 0, 0, 1, 0); break;
                case 2: setSquareFlags(flag, 0, 1, 0, 1, 0); break;
            }
            break;
        case 5:
            switch (random(3))
            {
                case 0: setSquareFlags(flag, 1, 1, 0, 1, 0); break;
                case 1: setSquareFlags(flag, 1, 0, 1, 1, 0); break;
                case 2: setSquareFlags(flag, 0, 0, 0, 0, 1); break;
            }
            break;
        case 6:
            switch (random(4))
            {
                case 0: setSquareFlags(flag, 1, 0, 1, 1, 0); break;
                case 1: setSquareFlags(flag, 1, 0, 0, 0, 1); break;
                case 2: setSquareFlags(flag, 0, 1, 1, 1, 0); break;
                case 3: setSquareFlags(flag, 0, 1, 0, 0, 1); break;
            }
            break;
        case 7:
            switch (random(3))
            {
                case 0: setSquareFlags(flag, 1, 1, 1, 1, 0); break;
                case 1: setSquareFlags(flag, 1, 1, 0, 0, 1); break;
                case 2: setSquareFlags(flag, 0, 0, 1, 0, 1); break;
            }
            break;
        case 8:
            switch (random(3))
            {
                case 0: setSquareFlags(flag, 1, 0, 1, 0, 1); break;
                case 1: setSquareFlags(flag, 0, 1, 1, 0, 1); break;
                case 2: setSquareFlags(flag, 0, 0, 0, 1, 1); break;
            }
            break;
        case 9:
            switch (random(3))
            {
                case 0: setSquareFlags(flag, 1, 1, 1, 0, 1); break;
                case 1: setSquareFlags(flag, 1, 0, 0, 1, 1); break;
                case 2: setSquareFlags(flag, 0, 1, 0, 1, 1); break;
            }
            break;
        case 10:
            switch (random(2))
            {
                case 0: setSquareFlags(flag, 1, 1, 0, 1, 1); break;
                case 1: setSquareFlags(flag, 0, 0, 1, 1, 1); break;
            }
            break;
        case 11:
            switch (random(2))
            {
                case 0: setSquareFlags(flag, 1, 0, 1, 1, 1); break;
                case 1: setSquareFlags(flag, 0, 1, 1, 1, 1); break;
            }
            break;
        case 12:
            setSquareFlags(flag, 1, 1, 1, 1, 1); break;
    }
}

void Clock::setSquareFlags(byte flag, bool square_1a, bool square_1b, bool square_2, bool square_3, bool square_5)
{
    if (square_1a) squareFlags[0] |= flag;
    if (square_1b) squareFlags[1] |= flag;
    if (square_2) squareFlags[2] |= flag;
    if (square_3) squareFlags[3] |= flag;
    if (square_5) squareFlags[4] |= flag;
}

void Clock::printTime(DateTime now)
{
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.println(now.second(), DEC);
}