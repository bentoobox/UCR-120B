#include "Timer.h"

#define BUTTON_PIN 2
#define LED_PIN 10

enum STATE { OFF, SLOW_FLASH, FAST_FLASH } gState = OFF;
unsigned char buttonState = 0;
unsigned char lastButtonState = 0;
unsigned int tickCounter = 0; // Counter for tracking ticks

void tick(void) {
  // Read the state of the button
  buttonState = digitalRead(BUTTON_PIN);

  // Check for button press
  if (buttonState == HIGH && lastButtonState == LOW) {
    switch (gState) {
      case OFF:
        gState = SLOW_FLASH;
        break;
      case SLOW_FLASH:
        gState = FAST_FLASH;
        break;
      case FAST_FLASH:
        gState = OFF;
        break;
    }

    // Print the current state to the serial monitor
    Serial.print("State: ");
    Serial.println(gState);
  }

  lastButtonState = buttonState;

  // Perform actions based on the state
  switch (gState) {
    case OFF:
      digitalWrite(LED_PIN, LOW);
      break;
    case SLOW_FLASH:
      // Check if it's time to toggle the LED state
      if (tickCounter % 2 == 0) {
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      }
      tickCounter++;
      break;
    case FAST_FLASH:
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      break;
  }
}

void setup() {
  TimerSet(500); // this value (500) is the period in ms
  TimerOn();
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  // Initialize the serial communication
  Serial.begin(9600);
}

void loop() {
  tick();
  while (!TimerFlag) {
  }
  TimerFlag = 0;
}
