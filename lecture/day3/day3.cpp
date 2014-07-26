int ports [5] = {9,10,11};   // the pin that the LED is attached to
int adder = 1;
int inc = 0;

// the setup routine runs once when you press reset:
void setup() {                
  for(int inc=0; inc < 5; inc++){
    // declare pincn 9 to be an output:
    pinMode(ports[inc], OUTPUT);
  }
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
// ----- Blink  

  // stop the bulbs from breaking
  if(voltage*200 < 5){
    voltage = 0.025;
  }

  digitalWrite(ports[inc], LOW);    // turn the LED off
  delay(voltage*200);
  digitalWrite(ports[inc], HIGH);   // turn the LED on
  delay(voltage);

  inc = inc + adder;

  // reverse the direction of the fading at the ends of the fade: 
  if (inc == 0 || inc == 4) {
    adder = -adder ; 
  }
  

  // set the brightness of pin 9:
  analogWrite(led, brightness);    

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade: 
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  }     
  // wait for 30 milliseconds to see the dimming effect    
  delay(30);
}

  NOTE_C7, NOTE_G7, NOTE_E7, NOTE_A7, NOTE_B7, NOTE_A3, NOTE_A7, NOTE_G7, NOTE_E7, NOTE_G3, NOTE_A3, NOTE_F3, NOTE_G3, NOTE_E3, NOTE_C3, NOTE_D3, NOTE_B3};
