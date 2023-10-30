#include "Timer.h"

#define LED_PIN 9
#define PHOTO_RESISTOR_PIN A0

enum STATE { INIT, DARK_WAIT, LIGHT_WAIT } gState = INIT;
unsigned long darkStartTime = 0;

void tick(void) {
  // transitions
  switch (gState) {
    case INIT:
      gState = DARK_WAIT;
      break;

    case DARK_WAIT:
      if (isDarkFor(5)) {  // 5 seconds
        gState = LIGHT_WAIT;
        digitalWrite(LED_PIN, HIGH); // Turn on the LED
      }
      break;

    case LIGHT_WAIT:
      if (isLight()) {
        gState = DARK_WAIT;
        digitalWrite(LED_PIN, LOW); // Turn off the LED
        darkStartTime = 0;
      }
      break;
  }
}

bool isDarkFor(unsigned long duration) {
  int lightValue = analogRead(PHOTO_RESISTOR_PIN);
  if (lightValue < 200) {
    if (darkStartTime == 0) {
      darkStartTime = millis() / 1000;  // Convert to seconds
    }
    return ((millis() / 1000) - darkStartTime >= duration);  // Convert to seconds
  } else {
    darkStartTime = 0;
    return false;
  }
}

bool isLight() {
  int lightValue = analogRead(PHOTO_RESISTOR_PIN);
  return lightValue >= 200; // Adjust the threshold as needed
}

void setup() {
  TimerSet(1000); // Set the timer for 1 second (1 tick)
  TimerOn();
  pinMode(LED_PIN, OUTPUT);
  pinMode(PHOTO_RESISTOR_PIN, INPUT);

  // Initialize the LED as off
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  tick();
  while (!TimerFlag) {
  }
  TimerFlag = 0;
}
