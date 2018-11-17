#include "FastLED.h"

#define NUM_LEDS 24
#define DATA_PIN 5
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

int fadeAmount = 5;
int brightness = 0;

int off = 255;
int minimun = 255;
int medium = 100;
int maximun = 0;

int delayInterval = 70;

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(115200);
  //reset();
  resetNew();
}

void turnOffStrip() {

}

//---
void fade() {
  for (int i = 0; i < NUM_LEDS; i++ ) {
    leds[i].setRGB(0, 0, 255);
    leds[i].fadeLightBy(brightness);
  }
  FastLED.show();
  brightness = brightness + fadeAmount;
  // reverse the direction of the fading at the ends of the fade:
  if (brightness == 0 || brightness == 220) {
    Serial.println(fadeAmount);
    fadeAmount = -fadeAmount ;
    Serial.println(fadeAmount);
  }
  delay(40);
}

void fadeIn() {
  for (int i = 0; i < NUM_LEDS; i++ ) {
    leds[i].setRGB(0, 0, 255);
    leds[i].fadeLightBy(brightness);
  }
  FastLED.show();
  brightness = brightness + fadeAmount;
  // reverse the direction of the fading at the ends of the fade:
  if (brightness == 0 || brightness == 220) {
    Serial.println(fadeAmount);
    fadeAmount = -fadeAmount ;
    Serial.println(fadeAmount);
  }
  delay(40);
}

void fade(int quantity) {

  for (int repeat = 0; repeat < quantity; repeat++ ) {
    brightness = 0;
    while (brightness < 220) {
      for (int i = 0; i < NUM_LEDS; i++ ) {
        leds[i].setRGB(0, 0, 255);
        leds[i].fadeLightBy(brightness);
      }
      FastLED.show();
      brightness = brightness - fadeAmount;
      delay(40);
    }
  }
}

void fadePin() {
  Serial.println("aueee");
  for (int i = 0; i < NUM_LEDS; i++ ) {
    leds[i].setRGB(0, 255, 0);
    FastLED.show();
  }

  for (int i = 255; i > 0; i--) {
    leds[7].setRGB(0, 255, 0);
    leds[7].fadeLightBy(i);
    FastLED.show();
    Serial.println(i);
    delay(100);
  }
}
void snack() {

  for (int i = 0; i < 24; i++ ) {
    leds[i] = CRGB::Blue;
    if (i > 7) {
      leds[i - 8] = CRGB::Black;
    }
    FastLED.show();
    delay(20);
  }

  for (int i = 16; i < 24; i++ ) {
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(20);
  }

}

void reset() {
  for (int i = 0; i < 8; i++ ) {
    leds[i] = CRGB::Blue;
    leds[i].fadeLightBy(minimun);
    FastLED.show();
  }
  for (int i = 8; i < 16; i++ ) {
    leds[i] = CRGB::Blue;
    leds[i].fadeLightBy(medium);
    FastLED.show();
  }
  for (int i = 16; i < 24; i++ ) {
    leds[i] = CRGB::Blue;
    leds[i].fadeLightBy(maximun);
    FastLED.show();
  }
}



void done() {
  for (int i = 0; i < 8; i++ ) {
    Serial.print(i);
    Serial.print(" - ");
    Serial.println(i);
    leds[i] = CRGB::Blue;
    leds[i].fadeLightBy(maximun);

    Serial.print(i);
    Serial.print(" - ");
    Serial.println(i + 8);
    leds[i + 8] = CRGB::Blue;
    leds[i + 8].fadeLightBy(minimun);

    Serial.print(i);
    Serial.print(" - ");
    Serial.println(i + 16);
    leds[i + 16] = CRGB::Blue;
    leds[i + 16].fadeLightBy(medium);
    FastLED.show();
    delay(delayInterval);
  }

  for (int i = 0; i < 8; i++ ) {
    Serial.print(i);
    Serial.print(" - ");
    Serial.println(i);
    leds[i] = CRGB::Blue;
    leds[i].fadeLightBy(medium);

    Serial.print(i);
    Serial.print(" - ");
    Serial.println(i + 8);
    leds[i + 8] = CRGB::Blue;
    leds[i + 8].fadeLightBy(maximun);

    Serial.print(i);
    Serial.print(" - ");
    Serial.println(i + 16);
    leds[i + 16] = CRGB::Blue;
    leds[i + 16].fadeLightBy(minimun);
    FastLED.show();
    delay(delayInterval);
  }

  for (int i = 0; i < 8; i++ ) {
    Serial.print(i);
    Serial.print(" - ");
    Serial.println(i);
    leds[i] = CRGB::Blue;
    leds[i].fadeLightBy(minimun);

    Serial.print(i);
    Serial.print(" - ");
    Serial.println(i + 8);
    leds[i + 8] = CRGB::Blue;
    leds[i + 8].fadeLightBy(medium);

    Serial.print(i);
    Serial.print(" - ");
    Serial.println(i + 16);
    leds[i + 16] = CRGB::Blue;
    leds[i + 16].fadeLightBy(maximun);
    FastLED.show();
    delay(delayInterval);
  }
}

int divisor = 8;
int slice = NUM_LEDS / divisor;

void resetNew() {
  for (int i = 0; i < NUM_LEDS; i++ ) {
    leds[i] = CRGB::Blue;
    leds[i].fadeLightBy(maximun);
    Serial.print("i: ");
    Serial.println(i);
    for (int j = 1; j < i; j++) {
      leds[j] = CRGB::Blue;
      //Serial.println("Passou aqui");
      int intensity = (minimun / j);
      leds[j].fadeLightBy(intensity);
      Serial.print("(");
      Serial.print(j);
      Serial.print("-");
      Serial.print(intensity);
      Serial.println(")");
    }
    Serial.println("------------------");
    FastLED.show();
  }
}

void doneNew() {
  for (int i = 0; i < NUM_LEDS; i++ ) {

    int acumulator = 1;
    for (int j = i - 1; j > 0; j--) {
      leds[j] = CRGB::Blue;
      int intensity = (minimun / NUM_LEDS) * acumulator;
      acumulator++;

      leds[j].fadeLightBy(intensity);
      Serial.print("(");
      Serial.print(j);
      Serial.print("-");
      Serial.print(intensity);
      Serial.println(")");
    }

    leds[i] = CRGB::Blue;
    leds[i].fadeLightBy(maximun);
    Serial.print("i- ");
    Serial.print("(");
    Serial.print(i);
    Serial.print("-");
    Serial.print(maximun);
    Serial.println(")");

    Serial.println("--");
    acumulator = 1;
    for (int j = i + 1; j < NUM_LEDS; j++) {
      leds[j] = CRGB::Blue;
      int intensity = minimun - ((minimun / NUM_LEDS) * acumulator);
      acumulator++;
      leds[j].fadeLightBy(intensity);
      Serial.print("(");
      Serial.print(j);
      Serial.print("-");
      Serial.print(intensity);
      Serial.println(")");
    }
    delay(delayInterval);
    Serial.println("------------------");
    FastLED.show();
  }
}
void loop() {
  fade(1);
}
