#include "FastLED.h"

#include "leds.h"
#include "constants.h"

void Leds::begin()
{
    FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
}

void Leds::setSquareColor(int squareIndex, CRGB color)
{
    applyBrightness(&color);

    switch (squareIndex) {
        case 0: leds[9] = color; break;
        case 1: leds[8] = color; break;
        case 2: leds[7] = color; break;
        case 3: leds[5] = leds[6] = color; break;
        case 4: leds[0] = leds[1] = leds[2] = leds[3] = leds[4] = color; break;
    }
}

void Leds::setBrightness(int brightness)
{
    brightness = constrain(brightness, 0, MAX_BRIGHTNESS);

    // If the brightness is already the same, don't do anything
    if (this->brightness == brightness) return;

    this->brightness = brightness;

    for (int i = 0; i < NUM_LEDS; i++) applyBrightness(&leds[i]);

    show();
}

void Leds::applyBrightness(CRGB* color)
{
    color->maximizeBrightness();

    if (brightness != MAX_BRIGHTNESS)
    {
        int fade = 255 - (brightness * 255.0 / MAX_BRIGHTNESS);

        // If the brightness is set to zero, fade by 230/256ths because fading to 255/256ths turns off the LEDs
        if (brightness == 0) fade = 230;
        color->fadeLightBy(fade);
    }
}

void Leds::show()
{
    FastLED.show();
}

void Leds::off()
{
    FastLED.clear(true);
}