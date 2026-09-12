#pragma once
#include <FastLED.h>
#include <Arduino.h>
#include "parametersLED.h"

class LEDEffect {
public:
    virtual ~LEDEffect() {}
    virtual void run(CRGB* leds, int count, ParamLED* pr) = 0;
    virtual LEDEffect* clone(int index) = 0;
};
//Радуга
class RainbowEffect : public LEDEffect {
private:
    uint8_t hue = 0;
public:
    LEDEffect* clone(int index) override {
        return new RainbowEffect();
    }

    void run(CRGB* leds, int count, ParamLED* pr) override {
        static unsigned long lastTime = 0;
        if (millis() - lastTime >= pr->speedEffect) {
            lastTime = millis();
            fill_rainbow(leds, count, hue, 7);
            hue++;
        }
    }
};
//конфети
class ConfettiEffect : public RainbowEffect {
public:
    LEDEffect* clone(int index) override {
        if (index == 1) return new ConfettiEffect();

        return RainbowEffect::clone(index);
    }

    void run(CRGB* leds, int count, ParamLED* pr) override {
        static unsigned long lastTime = 0;
        if (millis() - lastTime >= pr->speedEffect) {
            lastTime = millis();
            fadeToBlackBy(leds, count, 10);
            int pos = random16(count);
            leds[pos] += CHSV(random8(), 255, 255);
        }
    }
};
//Огонь
class FireEffect : public ConfettiEffect {
public:
    LEDEffect* clone(int index) override {
        
        if (index == 2) return new FireEffect();
        
        return ConfettiEffect::clone(index);
    }

    void run(CRGB* leds, int count, ParamLED* pr) override {
        static unsigned long lastTime = 0;
        if (millis() - lastTime >= pr->speedEffect) {
            lastTime = millis();
            for (int i = 0; i < count; i++) {
                int flicker = random8(100, 255);
                leds[i] = CHSV(20, 255, flicker);
            }
        }
    }
};
//Один цвет
class FillCollor : public FireEffect{
public:  
    LEDEffect* clone(int index) override {
        if (index == 3) return new FillCollor();
        return FireEffect::clone(index);
    }

    void run(CRGB* leds, int count, ParamLED* pr) override {
        CRGB color = pr->solidColorLED;
        fill_solid(leds, count, pr->solidColorLED);
    }
};


// CRGB color = solidColorLED;  // автоматически распакует RRGGBB
// fill_solid(leds, NUM_LEDS, color);

LEDEffect* StartEffect = new FillCollor;

LEDEffect* StartChangeEffect(int index)
{
    return StartEffect->clone(index);
}
