bool lock = true;

void setup(){
  Serial.begin(9600);
}

void loop(){
  char string;

  while(Serial.available() > 0){
    char nextChar = Serial.read();
    string += nextChar;
  }

  if(string == 'hello'){
    lock = false;
  }
  if(Serial.available() >= 1){
    Serial.println("Please enter a passphrase");
    Serial.println("you wrote"+string);
  }

  if(lock){
    analogWrite(11, 255);
  }else{

  }

}