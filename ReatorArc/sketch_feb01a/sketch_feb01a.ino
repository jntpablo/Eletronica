#include "FastLED.h"

#define NUM_LEDS 24
#define DATA_PIN 5
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

int fadeAmount = 5;
int brightness = 0;
int off = 255;
int minimun = 210;
int medium = 100;
int maximun = 0;

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(115200);

}

void fadeOut() {
  brightness = 0;
  while (brightness < 240) {
    for (int i = 0; i < NUM_LEDS; i++ ) {
      leds[i].setRGB(0, 0, 255);
      leds[i].fadeLightBy(brightness);
    }
    FastLED.show();
    brightness = brightness + fadeAmount;
    delay(30);
  }
}

void fadeIn() {
  brightness = 240;
  while (brightness > 0) {
    for (int i = 0; i < NUM_LEDS; i++ ) {
      leds[i].setRGB(0, 0, 255);
      leds[i].fadeLightBy(brightness);
    }
    FastLED.show();
    brightness = brightness - fadeAmount;
    delay(30);
  }
}

void fade(int repetitions) {
  for (int i = 0; i < repetitions; i++ ) {
    fadeIn();
    fadeOut();
  }
}

void wheel(int repetitions) {
  int delayInterval = 70;
  for (int repeat = 0; repeat < repetitions; repeat++ ) {
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
}
void loop() {
  fade(1);
  fadeIn();
  wheel(3);
  fadeOut();
  fade(1);
}
