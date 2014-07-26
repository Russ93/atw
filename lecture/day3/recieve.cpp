void setup(){
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
}

void loop(){
  while(Serial.available() >= 1){
    char color = Serial.read();
    int incomingValue = Serial.parseInt();
    if(color == 'r'){
      analogWrite(11, 255-incomingValue);
    }
    if(color == 'g'){
    	analogWrite(9, 255-incomingValue);
    }
    if(color == 'b'){
    	analogWrite(10, 255-incomingValue);
    }
      
    Serial.println(incomingValue);
  }
}