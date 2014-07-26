 #include "pitches.h"

int ports [] = {3,4,5,6,7};   // the pin that the LED is attached to
int adder = 1;
int inc = 0;
int pin = 8;
int monitorPin = 12;
bool trip;

void setup(){
  for(int inc=0; inc < 5; inc++){
    // declare pincn 9 to be an output:
    pinMode(ports[inc], OUTPUT);
  }
  pinMode(monitorPin, INPUT_PULLUP);
//  pinMode(12, OUTPUT);
  Serial.begin(9600);
}
void loop(){
// ----- Blink

  digitalWrite(ports[inc], HIGH);   // turn the LED on
  delay(500);

// ----- Button Pressing

  if(digitalRead(monitorPin) == LOW && ports[inc] == 5 ){
    Serial.println("You've Won!");
    trip = !trip;
    play();
  }
  delay(1);

  digitalWrite(ports[inc], LOW);    // turn the LED off
  delay(2);


  inc = inc + adder;

  // reverse the direction of the fading at the ends of the fade: 
  if (inc == 0 || inc == 4) {
    adder = -adder ; 
  }

}

void play(){
  // notes in the melody:
  int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

  // note durations: 4 = quarter note, 8 = eighth note, etc.:
  int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };
  
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(pin, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(pin);
  }
}
