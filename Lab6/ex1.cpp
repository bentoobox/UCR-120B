#include "Timer.h"

enum LD_States {ltR, rtL, pauseL, pauseR} LD_State;

char iterCnt;
char curr;
int score = 0;

char gSegPins[] = {11,12};

void TickFct_LDStates() {
  switch (LD_State) {
    case ltR: // LED shift left to right
      if(!digitalRead(13)){
        LD_State=pauseL;
      }else if(curr>9){
        LD_State=rtL;
      }
      break;
    case rtL: // LED shift right to left
      if(!digitalRead(13)){
        LD_State=pauseR;
      }else if(curr<5){
        LD_State=ltR;
      }
      break;
    case pauseL: // Pause increment on button hold
      if(digitalRead(13)){
        LD_State=ltR;
        if(digitalRead(7)){
          score++;
        }else{
          score=0;
        }
      }
      break;
    case pauseR:
      if(digitalRead(13)){
        LD_State=rtL;
        if(digitalRead(7)){
        score++;
        }else{
          score=0;
        }
      }
      break;
    default:
        LD_State = ltR;
        Serial.print("ERROR");
    }
  //part 2 ACTIONS
  switch (LD_State) {
    case ltR: // LED shift left to right
      digitalWrite(curr,LOW);
      curr++;
      digitalWrite(curr,HIGH);
      break;
    case rtL: // LED shift right to left
      digitalWrite(curr,LOW);
      curr--;
      digitalWrite(curr,HIGH);
      break;
    case pauseL: // Pause increment on button hold
      break;
    case pauseR: // Pause increment on button hold
      break;
    default:
        LD_State = ltR;
        Serial.print("ERROR");
    }
}

void displayDigit(int number, int digitPin) {
  // Initialize segment pins as outputs
  for (int i = 0; i < 7; i++) {
    pinMode(A0 + i, OUTPUT);
  }

  // Determine which segments to turn on based on the input number
  switch (number) {
    case 0:
      digitalWrite(A0, HIGH);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, HIGH);
      digitalWrite(A3, HIGH);
      digitalWrite(A4, HIGH);
      digitalWrite(A5, HIGH);
      digitalWrite(A6, LOW);
      break;

    case 1:
      digitalWrite(A1, HIGH);
      digitalWrite(A2, HIGH);
      break;

    case 2:
      digitalWrite(A0, HIGH);
      digitalWrite(A1, HIGH);
      digitalWrite(A3, HIGH);
      digitalWrite(A4, HIGH);
      digitalWrite(A6, HIGH);
      break;

    case 3:
      digitalWrite(A0, HIGH);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, HIGH);
      digitalWrite(A3, HIGH);
      digitalWrite(A6, HIGH);
      break;

    case 4:
      digitalWrite(A1, HIGH);
      digitalWrite(A2, HIGH);
      digitalWrite(A5, HIGH);
      digitalWrite(A6, HIGH);
      break;

    case 5:
      digitalWrite(A0, HIGH);
      digitalWrite(A2, HIGH);
      digitalWrite(A3, HIGH);
      digitalWrite(A5, HIGH);
      digitalWrite(A6, HIGH);
      break;

    case 6:
      digitalWrite(A0, HIGH);
      digitalWrite(A2, HIGH);
      digitalWrite(A3, HIGH);
      digitalWrite(A4, HIGH);
      digitalWrite(A5, HIGH);
      digitalWrite(A6, HIGH);
      break;

    case 7:
      digitalWrite(A1, HIGH);
      digitalWrite(A2, HIGH);
      digitalWrite(A5, HIGH);
      break;

    case 8:
      digitalWrite(A0, HIGH);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, HIGH);
      digitalWrite(A3, HIGH);
      digitalWrite(A4, HIGH);
      digitalWrite(A5, HIGH);
      digitalWrite(A6, HIGH);
      break;

    case 9:
      digitalWrite(A0, HIGH);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, HIGH);
      digitalWrite(A3, HIGH);
      digitalWrite(A5, HIGH);
      digitalWrite(A6, HIGH);
      break;

    default:
      // Display blank
      break;
  }

  // Set the digit pin to high to enable the selected segment pins
  digitalWrite(digitPin, HIGH);

  // Delay for a short period to allow the display to update
  delay(10);

  // Clear all segment pins
  for (int i = 0; i < 7; i++) {
    digitalWrite(A0 + i, LOW);
  }

  // Turn off the digit pin to disable the segment pins
  digitalWrite(digitPin, LOW);
}


void setup() {

  Serial.begin(9600);

  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A6, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  TimerSet(100);
  TimerOn();

  iterCnt=0;
  curr=7;
  score=0;

}

void loop() {
  displayDigit(score%10, 12);
  displayDigit(score/10, 11);
  if(TimerFlag){
    //debug
    Serial.print("Score: ");
    Serial.println(score);
    //10ms run
    TickFct_LDStates();
  }
  TimerFlag = 0;
}
