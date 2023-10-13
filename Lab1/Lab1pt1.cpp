
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

}
int pointer =0;
bool response = false;
void loop()
{
if(Serial.available()>0){
  	pointer =Serial.parseInt();
  	Serial.println(pointer, DEC);
	response= true;
}
if(response){
  	digitalWrite(pointer+1, HIGH);
  	delay(500); 
  	digitalWrite(pointer+1, LOW);
	pointer--;	
	if(pointer==0)
      pointer=1;
  }
}
