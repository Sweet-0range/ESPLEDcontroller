#pragma once
#include <FastLED.h>

#define LED_PIN 2
#define MAX_LEDS 100

class ESPLED
{
private:
  CRGB* LEDS = nullptr;
  int brightnessLED;
  int countLED;

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
    this->brightnessLED = brightness;
    FastLED.setBrightness(brightness);
    FastLED.clear(true);
    return true;
  }

  bool drawOnLED()
  {
    static uint8_t hue;
    fill_rainbow(LEDS, countLED, hue, 7);
    FastLED.show();
    hue++;
    return true;
  }

};
