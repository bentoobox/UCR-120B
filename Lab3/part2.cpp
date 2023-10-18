// C++ code
//
const int buttonPin = 13; // Define the button pin
int buttonState = 0;     // Variable to store the button state
int sel = 2;
bool curr = false;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  buttonState = digitalRead(buttonPin); // Read the button state
  Serial.print("Button State:");
  Serial.println(digitalRead(13));
  if(curr&&buttonState==HIGH){
  curr=false;
  }
  if(!curr&&buttonState==LOW){
  sel+=1;
  Serial.println("BRANCH");
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);

  curr=true;
  }
  	digitalWrite(((sel%3)+2),HIGH);
    Serial.print("Sel:");
  	Serial.println(sel);
  delay(100);
}
