
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

}
int pointer =0;
bool response = false;
void loop(){
  	//digitalWrite(2, HIGH);
	if(Serial.available()>0){
  		pointer =Serial.parseInt();
  		Serial.println(pointer, DEC);
		response=true;
    }
  	if(response){
		if(pointer<65){
  			digitalWrite(2, HIGH);
  			//delay(500); 
		}else if(pointer<95){
			digitalWrite(3, HIGH);
		}else{
			digitalWrite(4, HIGH);
		}
    }
}
