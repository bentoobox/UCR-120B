#include <LiquidCrystal.h>
#include "Timer.h"

LiquidCrystal lcd(12, 11, 5,4,3,2);

enum SA_States {initial, input} SA_State;
String inputString;
int specialCharacterCount = 0;
bool inputBool = false;
void Tag_Latch(){
  //Serial.println(SA_State);
  
  const char specialCharacters[] = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '{', '}', '[', ']', '/', '\\', '|', '-', '_', '=', '+', '~', '`', ':', ';', '"', '\'', ','};
  
  

  switch(SA_State){
    case initial:
      SA_State= input;
      break;
    case input:
      Serial.print("value before check: ");
      Serial.println(specialCharacterCount);
      if((specialCharacterCount<3)){
        specialCharacterCount = 0;
        Serial.println("FAILED TRY AGAIN");
        SA_State = input;
        
      }else if(inputBool == false){
        //move cursor
        //lcd.print("This is a test");
        lcd.print(inputString);
        Serial.println("MOVING ON TO #2");
        lcd.setCursor(0, 1);
        inputBool=true;
        SA_State = input;
        specialCharacterCount=0;
      }else{
        Serial.println("STALLING");
        lcd.print(inputString);
        //idle engine
        while(1){
          TimerISR();
        }
        SA_State= initial;
        specialCharacterCount=0;
      }
      break;
    default:
      SA_State=initial;
      break;
  }
  switch(SA_State){
    case initial:
      lcd.clear();
      break;
    
    case input:
      Serial.print("Enter a string with 3 unique special characters: ");
      while (!Serial.available()) {
        
        TimerISR();
      }

      inputString = Serial.readString();
      bool uniqueSpecialCharacters[256] = {false};
      for (char c : inputString) {
        bool found = false;
        for (char specialCharacter : specialCharacters) {
          if ((c == specialCharacter)&&!uniqueSpecialCharacters[c]) {
            specialCharacterCount++;
            //Serial.print("specialCharacterCount:");
            //Serial.println(specialCharacterCount);
            uniqueSpecialCharacters[c]=true;
            found = true;
            break;
          }
        }
      }
      break;
    default:
      break;
  }
}

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.clear();
  Serial.println("SETUP COMPLETE");
  SA_State = initial;

  //timer function
  //TimerSet(1000);
  //TimerOn();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(SA_State);
  Serial.println("ITERATING");
  Tag_Latch();
  //Serial.println(SA_State);
}
