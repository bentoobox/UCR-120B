#include "Timer.h"

enum LED_States { led_init, theOnlyOneINeed } LED_State;
enum Btn_States { btn_init, wPress, wlift } Btn_State;

int joyXValue;
int joyYValue;
bool joyButtonState;
int offset;

const int LEDPins[] = { 6, 7, 8, 9, 10 };

void TickFct_BtnControl() {
    Serial.print("joyButtonState:");
    Serial.println(joyButtonState);
    switch (Btn_State) {
    case btn_init:
        Btn_State = wPress;
        joyButtonState = true;
        break;

    case wPress:
        if (digitalRead(13)) {
            joyButtonState = !joyButtonState;
            digitalWrite(6 + offset, joyButtonState); // Toggle LED based on button state
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

void TickFct_JoystickControl() {
    // Read joystick position and button state
    joyXValue = analogRead(A1);
    joyYValue = analogRead(A0);
    //joyButtonState = digitalRead(13);

    // Update LED state based on joystick position
    switch (LED_State) {
    case led_init:
        offset = 2;
        digitalWrite(6 + offset, HIGH);
        LED_State = theOnlyOneINeed;
        break;

    case theOnlyOneINeed:
        if ((joyXValue < 15) && (offset > 0)) {
            digitalWrite(6 + offset, LOW);
            offset--;
            digitalWrite(6 + offset, joyButtonState);
            LED_State = theOnlyOneINeed;
        } else if ((joyXValue > 1022) && (offset < 4)) {
            digitalWrite(6 + offset, LOW);
            offset++;
            digitalWrite(6 + offset, joyButtonState);
            LED_State = theOnlyOneINeed;
        }
        break;

    default:
        LED_State = led_init;
        break;
    }
}

void setup() {
    Serial.begin(9600);
    TimerSet(100);
    TimerOn();
}

int timer = 0;

void loop() {
    //Serial.print("JOYSTATE: ");
    //Serial.println(analogRead(A1));

    if (timer == 5) {
        //Serial.print("OFFSET: ");
        //Serial.println(offset);
        //Serial.print("button: ");
        //Serial.println(joyButtonState);
        TickFct_JoystickControl();
    }
    if(timer>10){
      TickFct_BtnControl();
      timer=0;
    }
    //Serial.println(TimerFlag);

    if (TimerFlag) {
        timer++;
    }
}
