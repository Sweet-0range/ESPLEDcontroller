#include <FastLED.h>
#include <SettingsGyver.h>
#include <LittleFS.h>
#include <Arduino.h>
#include "classLed.h"
#include "classLEDEffects.h"

//Wi-Fi
#define WIFI_SSID "Ufanet-12"
#define WIFI_PASS "AdminAdmin2005"

//Setting Татле
SettingsGyver sett("Управление Лентой");

//Переменные
bool ChangeFlag = false;
int brightnessLED = 50;
int countLED = 10;
int effectLED = 0;
unsigned long speedEffectLED=7;

//ESPLED
ESPLED LEDStrip;

//Создание страницы
void build(sets::Builder& b) {
  if(b.Slider("bright"_h, "Яркость", 0, 50, 1, "", &brightnessLED))
    {LEDStrip.ChangeBrightnessLED(brightnessLED);}
  if(b.Slider("speed"_h, "Скорость", 0, 20, 1, "", &speedEffectLED))
    {LEDStrip.ChangeSpeedEffect(speedEffectLED);}
  if(b.Number("count"_h, "LED Count", &countLED))
    {LEDStrip.ChangeCountLED(countLED);}

  if(b.Select("effect"_h, "Эффект",
             "Радуга;Конфети;Огонь;Синий",
             &effectLED)){
             LEDStrip.ChangeEffect(effectLED);
             }
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  //Подключение к Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected: ");
  Serial.println(WiFi.localIP());

  sett.begin();
  sett.onBuild(build);

  if(LEDStrip.buld(brightnessLED, countLED))
    Serial.println("Start");
}

void loop() {
  sett.tick();

  LEDStrip.displayEffect();
}
