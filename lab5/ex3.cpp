#include <LiquidCrystal.h>
#include "Timer.h"

LiquidCrystal lcd(12, 11, 5,4,3,2);

enum SA_States {initial, input} SA_State;
enum Btn_States { btn_init, wPress, wlift } Btn_State;
int charCount = 0;
bool inputBool = false;
int timer;
int xPos=0;
int yPos=0;

void TickFct_BtnControl() {
    switch (Btn_State) {
    case btn_init:
        Btn_State = wPress;
        break;

    case wPress:
        if (digitalRead(13)) {
            lcd.write("#");
            charCount++;
            Serial.println("write");
            Btn_State = wlift;
        } else {
            Btn_State = wPress;
        }
        break;

    case wlift:
        if (!digitalRead(13)) {
            Btn_State = wPress;
        }
        break;

    default:
        Btn_State = btn_init;
        Serial.print("ERROR");
    }
}

void Tag_Latch(){
  //Serial.println(SA_State);
  
  switch(SA_State){
    case initial:
      SA_State= input;
      break;
    case input:
      if(charCount>4){
        SA_State=initial;
      }
      break;
    default:
      SA_State=initial;
      break;
  }
  ///////////////////////
  Serial.print(xPos);
  Serial.print(" - ");
  Serial.println(yPos);
  switch(SA_State){
    case initial:
      lcd.clear();
      lcd.setCursor(0, 0);
      xPos=0;
      yPos=0;
      charCount=0;
      //lcd.blink();
      break;
    
    case input:
    if(analogRead(A1)>900){
      xPos++;
    }else if(analogRead(A1)<10){
      xPos--;
    }
    if(analogRead(A0)>900){
      yPos++;
    }else if(analogRead(A0)<10){
      yPos--;
    }
    //trim
    if(xPos>15){
      xPos=15;
    }else if(xPos<0){
      xPos=0;
    }
    if(yPos>2){
      yPos=2;
    }else if(yPos<0){
      yPos=0;
    }
    lcd.setCursor(xPos,yPos);
      break;
    default:
      break;
  }
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  SA_State = initial;
    TimerSet(100);
  TimerOn();
  timer=0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.cursor();
  lcd.blink();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(SA_State);
  //Serial.println(SA_State);
  
  if(TimerFlag){
    Serial.println("ITERATING");
    timer++;
  }
  if(timer>50){
    Serial.println("flag");
    TickFct_BtnControl();
    Tag_Latch();
timer=0;
  }
}
