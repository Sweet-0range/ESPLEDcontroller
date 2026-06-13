#pragma once

#include <FastLED.h>

#define LED_PIN 2
#define MAX_LEDS 100

unsigned long GlobalTimer = 0;

class ESPLED
{
private:
    CRGB* LEDS = nullptr;
    int brightnessLED;
    int countLED;
    unsigned long speedEffect = 7;

public:


    bool buld(int brightness, int count)
    {
        countLED = constrain(count, 1, MAX_LEDS);
        brightnessLED = constrain(brightness, 0, 50);
        FastLED.clear(true);
        if(LEDS!=nullptr)
            delete[] LEDS;

        LEDS = new CRGB[countLED];
        this->brightnessLED = brightness;
        this->countLED = countLED;

        FastLED.clear(true);
        FastLED.addLeds<WS2812B, LED_PIN, GRB>(LEDS, countLED);
        FastLED.setBrightness(brightness);
        FastLED.clear(true);
        return true;
    }

    bool ChangeCountLED(int count)
    {
        FastLED.clear(true);
        countLED = constrain(count, 1, MAX_LEDS);
        if(LEDS!=nullptr)
            delete[] LEDS;

        //FastLED.clear(true);
        LEDS = new CRGB[countLED];
        this->countLED = count;

        FastLED.addLeds<WS2812B, LED_PIN, GRB>(LEDS, countLED);
        FastLED.clear(true);
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

    bool displayEffect()
    {
      static uint8_t hue = 0;
      if (millis() - GlobalTimer >= speedEffect)
      {
        GlobalTimer = millis();
        fill_rainbow(LEDS,countLED,hue,7);

        FastLED.show();
        hue++;
      }

      return true;
    }
};