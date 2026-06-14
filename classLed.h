#pragma once

#include <FastLED.h>
#include "classLEDEffects.h"

#define LED_PIN 2
#define MAX_LEDS 100

class ESPLED
{
private:
    CRGB* LEDS = nullptr;
    int brightnessLED;
    int countLED;
    unsigned long speedEffect = 7;

    bool isUpdating = false;

    LEDEffect* Effect= new RainbowEffect;

public:

    bool buld(int brightness, int count)
    {
        countLED = constrain(count, 1, MAX_LEDS);
        brightnessLED = constrain(brightness, 0, 50);
        if(LEDS!=nullptr)
            delete[] LEDS;

        LEDS = new CRGB[countLED];
        this->brightnessLED = brightness;
        this->countLED = countLED;

        FastLED.addLeds<WS2812B, LED_PIN, GRB>(LEDS, countLED);
        FastLED.setBrightness(brightness);
        FastLED.clear();
        FastLED.show();
        return true;
    }

    bool ChangeCountLED(int count)
    {
        isUpdating = true;
        FastLED.clear(true);
        countLED = constrain(count, 1, MAX_LEDS);
        if(LEDS!=nullptr)
            delete[] LEDS;

        LEDS = new CRGB[countLED];
        if (!LEDS) {
            isUpdating = false;
            return false;
        }

        FastLED.addLeds<WS2812B, LED_PIN, GRB>(LEDS, countLED);
        FastLED.clear();
        FastLED.show();
        isUpdating = false;
        return true;
    }

    bool ChangeBrightnessLED(int brightness)
    {
        brightnessLED = constrain(brightness, 0, 50);

        FastLED.setBrightness(brightnessLED);

        return true;
    }

    bool ChangeSpeedEffect(unsigned long time = 50)
    {
        speedEffect = time;

        return true;
    }

    bool ChangeEffect(int Index) {

        if(Effect != nullptr) delete Effect;
        
        Effect = StartChangeEffect(Index);
        FastLED.clear();
        FastLED.show();
        return true;
    }

    bool displayEffect() {
    if (!isUpdating && Effect != nullptr && LEDS != nullptr) {
        Effect->run(LEDS, countLED, speedEffect);
        FastLED.show();
    }
    return true;
    }
};