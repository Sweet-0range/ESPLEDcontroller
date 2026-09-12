#pragma once
#include <FastLED.h>
#include <Arduino.h>

class LEDEffect {
public:
    virtual ~LEDEffect() {}
    virtual void run(CRGB* leds, int count, unsigned long speed) = 0;
    virtual LEDEffect* clone(int index) = 0;
};

class RainbowEffect : public LEDEffect {
private:
    uint8_t hue = 0;
public:
    LEDEffect* clone(int index) override {
        return new RainbowEffect();
    }
    void run(CRGB* leds, int count, unsigned long speed) override {
        static unsigned long lastTime = 0;
        if (millis() - lastTime >= speed) {
            lastTime = millis();
            fill_rainbow(leds, count, hue, 7);
            hue++;
        }
    }
};

class ConfettiEffect : public RainbowEffect {
public:
    LEDEffect* clone(int index) override {
        if (index == 1) {
            return new ConfettiEffect();
        }
        return RainbowEffect::clone(index);
    }
    void run(CRGB* leds, int count, unsigned long speed) override {
        static unsigned long lastTime = 0;
        if (millis() - lastTime >= speed) {
            lastTime = millis();
            fadeToBlackBy(leds, count, 10);
            int pos = random16(count);
            leds[pos] += CHSV(random8(), 255, 255);
        }
    }
};

class FireEffect : public ConfettiEffect {
public:
    LEDEffect* clone(int index) override {
        if (index == 2) {
            return new FireEffect();
        }
        return ConfettiEffect::clone(index);
    }
    void run(CRGB* leds, int count, unsigned long speed) override {
        static unsigned long lastTime = 0;
        if (millis() - lastTime >= speed) {
            lastTime = millis();
            for (int i = 0; i < count; i++) {
                int flicker = random8(100, 255);
                leds[i] = CHSV(20, 255, flicker);
            }
        }
    }
};





LEDEffect* StartEffect = new FireEffect;

LEDEffect* StartChangeEffect(int index)
{
    return StartEffect->clone(index);
}
