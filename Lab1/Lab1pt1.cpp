
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
	for (int i = 2; i < 10; i++) {
  		pinMode(i, OUTPUT);
	}
}
int pointer =2;
int binary = 0;
bool response = false;
bool firstPart = true;;
String inputString;
char hexChar;
int binaryValue;
int decValue;

int hexToDec(char hexChar) {
  int decValue = 0;
  if (hexChar >= '0' && hexChar <= '9') {
    decValue = hexChar - '0';
  } else if (hexChar >= 'A' && hexChar <= 'F') {
    decValue = hexChar - 'A' + 10;
  }
  return decValue;
}

void loop()
{
  //Part 1
 if(firstPart){
	if(Serial.available()>0){
  		inputString = Serial.readString();
			decValue=hexToDec(inputString[0]);
      Serial.println(decValue);
      Serial.println(inputString[0]);
          if(inputString.length()>1){
			decValue=(decValue*16)+hexToDec(inputString[1]);
          }
		for (int i = 7; i >= 0; i--) {
    		binaryValue = decValue % 2; 
   		 	digitalWrite(9 - i, binaryValue);
    		decValue >>= 1;
  		}
    firstPart=false;
    }
 
 }else{
  //PART 2
	if(Serial.available()>0){
  		pointer =Serial.parseInt();
    	response=true;
    }
   if(response){
 		if(pointer>0){
          for(int i = 2;i<10;i++){
				Serial.println(digitalRead(i+1));
				digitalWrite(i,digitalRead(i+1));
          		digitalWrite(i+1,LOW);
        	}
			pointer--;  
			delay(500);
 		}
	}
 }}
