void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

}
int pointer=2;
double input =0;
int primitive=0;
bool response = false;
void loop(){
  	//digitalWrite(2, HIGH);
	if(Serial.available()>0){
  		input =Serial.parseInt();
  		Serial.println(input, DEC);
      	input = (5*(input-32))/9;
      	primitive = input;
      	Serial.print(primitive);
      	for(int i =2;i<6;i++){
    		digitalWrite(i,LOW);
    	}
		response=true;
    }
  	if(response&&pointer){
      if((primitive%2)>0){
      	digitalWrite(pointer, HIGH);
      }
      primitive/=2;
      pointer++;
    }
  if(pointer==6){
  	pointer=2;
    response=false;
  }
}
