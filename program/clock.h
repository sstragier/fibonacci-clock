#ifndef _FIB_CLOCK_H_
#define _FIB_CLOCK_H_

#include "Arduino.h"
#include "FastLED.h"
#include <RTClib.h>
#include <Wire.h>

#include "constants.h"

#define FLAG_HOUR_ON 0x01
#define FLAG_MINUTE_ON 0x02

class Clock {
private:
    RTC_DS3231 rtc;
    CRGB leds[NUM_LEDS];
    byte squareFlags[NUM_SQUARES];
    int prevHour = 9999;
    int prevMinute = 9999;

    void displayTime(int hour, int minute);
    void resetSquareFlags();
    void setSquareFlags(int value, byte flag);
    void setSquareFlags(byte flag, bool square_1a, bool square_1b, bool square_2, bool square_3, bool square_5);
    void updateLeds();
    void updateLed(int squareIndex, byte flags);

public:
    Clock();
    void begin();
    void loop();
    DateTime getTime();
    void setTime(DateTime now);
    void printTime(DateTime now);
};

#endif // _FIB_CLOCK_H_
