// C++ code
//
int codex[3];
int input_Code[3];
bool locked =false;
int input = 0;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void clear(int arr[]){
    for(int i = 0;i<3;i++){
    	arr[i]=0;
    }
}

bool inArray(int arr[], int target){
  for(int i = 0;i<sizeof(arr);i++){
    if(target==arr[i]){
    return true;
    }
  }
  return false;
}

int readIn(){
  int input;
  int iter = 3;
  while(true){
    //Serial.println(iter);
    if(digitalRead(11+(iter%3))==HIGH){
      while(0!=(digitalRead(11)+digitalRead(12)+digitalRead(13))){
      	//wait until lift
        delay(1);
      }
      	return((iter%3)+1);
    }else{
    iter++;
    }
  }
}

void inputArr(int arr[], int length){
  	int intake;
	for(int i =0;i<length;i++){
  		intake=readIn();
      	Serial.println(intake);
    	if(!inArray(arr, intake)){
    		arr[i]=intake;
          	//Serial.println(i);
        }else{
        	i--;
        }
  	}
    Serial.print(arr[0]);
    Serial.print(arr[1]);
    Serial.println(arr[2]);
}

//we could use a helper fucntion here for effeciency but that is outside of scope
//alternative is copy and paste since large memory
void loop()
{
  //ENCODING
  if(!locked){
    Serial.println("LOCKING");
 	inputArr(codex, 3);
  	//LOCKED
  	locked=true;
  	Serial.println("DEVICE_LOCKED");
  	digitalWrite(2,HIGH);
  }else{
  //DECODE
    clear(input_Code);
    Serial.println("READING");
    inputArr(input_Code, 3);
    //we use input as our check value;
    input=0;
    for(int i = 0;i<3;i++){
      if(codex[i]!=input_Code[i]){
      	Serial.print(codex[i]);
        Serial.print("=/=");
        Serial.println(input_Code[i]);
      	input++;
      }
    }
    if(input==0){
    	//UNLOCK_DEVICE
    	Serial.println("DEVICE_UNLOCKED");
      	locked=false;
    	digitalWrite(2,LOW);
      	clear(input_Code);
      	clear(codex);
    }
  }
  delay(1000);
}
