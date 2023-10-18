// C++ code
//
const int buttonPin = 13; // Define the button pin
int buttonState = 0;     // Variable to store the button state
bool flop = false;
bool curr = false;
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  //Serial.print("something");
  buttonState = digitalRead(buttonPin); // Read the button state
 //	  Serial.print(buttonState);
 if(curr&&buttonState==HIGH){
  curr=false;
  }
  if(!curr&&buttonState==LOW){
  	Serial.println("into Low");
    flop=!flop;
    Serial.println(flop);
    curr=true;
  }
      Serial.println(flop);
  if(!flop){
  	Serial.println("LED_high");
    digitalWrite(2,HIGH);
  }else{
      	Serial.println("LED_LOW");
  	digitalWrite(2,LOW);
  }
  delay(100);
}
