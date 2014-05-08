/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
int ports [5] = {3,5,6,9,10};   // the pin that the LED is attached to
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
// ----- Voltage
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);

// ----- Blink  

  // stop the bulbs from breaking
  if(voltage*200 < 5){
    voltage = 0.025;
  }

  digitalWrite(ports[inc], HIGH);   // turn the LED on
  delay(voltage*200);
  digitalWrite(ports[inc], LOW);    // turn the LED off
  delay(voltage);

  inc = inc + adder;

  // reverse the direction of the fading at the ends of the fade: 
  if (inc == 0 || inc == 4) {
    adder = -adder ; 
  }
  
}
