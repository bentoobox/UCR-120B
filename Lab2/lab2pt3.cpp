void setup()
{
  	pinMode(LED_BUILTIN, OUTPUT);
  	Serial.begin(9600);
	int mapped = 0;
}
	int prev=0;
void loop(){
  	//Serial.print(analogRead(A0));
  	//Serial.print("-");
  	int mapped = map(analogRead(A0),0,1023,0,4);
  	//Serial.print(mapped);
 	//Serial.print("|");
  if(prev!=mapped){
    prev=mapped;
    for(int i = 2;i<6;i++){
  		digitalWrite(i,LOW);
  	}
  	for(int i = 2;i<mapped+2;i++){
  		digitalWrite(i,HIGH);
  	}
  }
}
