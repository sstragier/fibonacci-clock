#include "FastLED.h"

#include "leds.h"
#include "constants.h"

void Leds::begin()
{
    FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
}

void Leds::setSquareColor(int squareIndex, CRGB color)
{
    switch (squareIndex) {
        case 0: leds[9] = color; break;
        case 1: leds[8] = color; break;
        case 2: leds[7] = color; break;
        case 3: leds[5] = leds[6] = color; break;
        case 4: leds[0] = leds[1] = leds[2] = leds[3] = leds[4] = color; break;
    }
}

void Leds::show()
{
    FastLED.show();
}