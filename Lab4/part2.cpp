#include "Timer.h"

#define BUTTON_PIN 2
#define RED_LED_PIN 10
#define YELLOW_LED_PIN 11
#define GREEN_LED_PIN 12

enum STATE { RED_ON, GREEN_ON, YELLOW_ON } gState = RED_ON;
unsigned char buttonState = 0;
unsigned char lastButtonState = 0;
unsigned int timeCounter = 0;

void tick(void) {
  // Read the state of the button
  buttonState = digitalRead(BUTTON_PIN);

  // Check for button press
  if (buttonState == HIGH && lastButtonState == LOW) {
    // If the button is pressed, transition to the next state
    switch (gState) {
      case RED_ON:
        gState = GREEN_ON;
        timeCounter = 0;
        break;
      case GREEN_ON:
        gState = YELLOW_ON;
        timeCounter = 0;
        break;
      case YELLOW_ON:
        gState = RED_ON;
        timeCounter = 0;
        break;
    }
  }

  lastButtonState = buttonState;

  // Perform actions based on the state
  switch (gState) {
    case RED_ON:
      digitalWrite(RED_LED_PIN, HIGH);
      digitalWrite(GREEN_LED_PIN, LOW);
      digitalWrite(YELLOW_LED_PIN, LOW);
      break;
    case GREEN_ON:
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(GREEN_LED_PIN, HIGH);
      digitalWrite(YELLOW_LED_PIN, LOW);
      break;
    case YELLOW_ON:
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(GREEN_LED_PIN, LOW);
      digitalWrite(YELLOW_LED_PIN, HIGH);
      break;
  }

  // Increment the time counter
  timeCounter++;

  // Handle state transitions based on time intervals
  if (timeCounter >= 10 && gState == GREEN_ON) {
    gState = YELLOW_ON;
    timeCounter = 0;
  } else if (timeCounter >= 5 && gState == YELLOW_ON) {
    gState = RED_ON;
    timeCounter = 0;
  }
}

void setup() {
  TimerSet(1000); // this value (1000) is the period in ms
  TimerOn();
  pinMode(BUTTON_PIN, INPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  // Initialize the LEDs
  digitalWrite(RED_LED_PIN, HIGH); // Start with the red LED on
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
}

void loop() {
  tick();
  while (!TimerFlag) {
  }
  TimerFlag = 0;
}
