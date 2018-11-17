#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN             5

#define NUMPIXELS      24

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 50; // delay for half a second

void setup() {
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  pixels.begin(); // This initializes the NeoPixel library.
  Serial.begin(115200);
}

void test() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 255));
    pixels.setBrightness(255);
    pixels.show();
    delay(delayval);
  }
}


void turnOffStrip() {
  for (int i = 0; i < NUMPIXELS; i++) {
    turnOff(i);
  }
}

void turnOnStrip() {
  for (int i = 0; i < NUMPIXELS; i++) {
    turnOn(i);
  }
}

void turnOn(int index) {
  pixels.setPixelColor(index, 0, 0, 255);
  pixels.setBrightness(255);
  pixels.show();
}

void turnOff(int index) {
  pixels.setPixelColor(index, pixels.Color(0, 0, 0));
  pixels.setBrightness(255);
  pixels.show();
}

void stripFadeIn(int delayInterval) {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 255));
    pixels.setBrightness(255);
    pixels.show();
    Serial.println(i);
  }
  delay(1000);
  for (int i = 0; i < 255; i++) {
    pixels.setBrightness(i);
    pixels.show();
    delay(delayInterval);
    Serial.println(i);
  }

}

void stripFadeOut(int delayInterval) {
  for (int i = 255; i > 0; i--) {
    pixels.setPixelColor(i, 0, 0, 255);
    pixels.setBrightness(i);
    pixels.show();
    delay(delayInterval);
  }
}
void loop() {
  //  turnOffStrip();
  //
  stripFadeIn(50);

  //  turnOnStrip();
  //  delay(10);
  //  turnOffStrip();
  //  delay(10);

  //  stripFadeOut(100);
}
