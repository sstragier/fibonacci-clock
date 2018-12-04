#ifndef _CLOCK_COLORS_H_
#define _CLOCK_COLORS_H_

#define MAX_PALETTES 10
#define TOTAL_PALETTES 10

CRGB black = CRGB(0, 0, 0);
CRGB colors[TOTAL_PALETTES][4] =
    {
        {
            // #1 RGB
            CRGB(255, 255, 255), // off
            CRGB(255, 10, 10),   // hours
            CRGB(10, 255, 10),   // minutes
            CRGB(10, 10, 255)    // both;
        },
        {
            // #2 Mondrian
            CRGB(255, 255, 255), // off
            CRGB(255, 10, 10),   // hours
            CRGB(248, 222, 0),   // minutes
            CRGB(10, 10, 255)    // both;
        },
        {
            // #3 Basbrun
            CRGB(255, 255, 255), // off
            CRGB(80, 40, 0),     // hours
            CRGB(20, 200, 20),   // minutes
            CRGB(255, 100, 10)   // both;
        },
        {
            // #4 80's
            CRGB(255, 255, 255), // off
            CRGB(245, 100, 201), // hours
            CRGB(114, 247, 54),  // minutes
            CRGB(113, 235, 219)  // both;
        },
        {
            // #5 Pastel
            CRGB(255, 255, 255), // off
            CRGB(255, 123, 123), // hours
            CRGB(143, 255, 112), // minutes
            CRGB(120, 120, 255)  // both;
        },
        {
            // #6 Modern
            CRGB(255, 255, 255), // off
            CRGB(212, 49, 45),   // hours
            CRGB(145, 210, 49),  // minutes
            CRGB(141, 95, 224)   // both;
        },
        {
            // #7 Cold
            CRGB(255, 255, 255), // off
            CRGB(209, 62, 200),  // hours
            CRGB(69, 232, 224),  // minutes
            CRGB(80, 70, 202)    // both;
        },
        {
            // #8 Warm
            CRGB(255, 255, 255), // off
            CRGB(237, 20, 20),   // hours
            CRGB(246, 243, 54),  // minutes
            CRGB(255, 126, 21)   // both;
        },
        {
            //#9 Earth
            CRGB(255, 255, 255), // off
            CRGB(70, 35, 0),     // hours
            CRGB(70, 122, 10),   // minutes
            CRGB(200, 182, 0)    // both;
        },
        {
            // #10 Dark
            CRGB(255, 255, 255), // off
            CRGB(211, 34, 34),   // hours
            CRGB(80, 151, 78),   // minutes
            CRGB(16, 24, 149)    // both;
        }};

#endif // _CLOCK_COLORS_H_