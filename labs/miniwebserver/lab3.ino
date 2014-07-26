/*
  Lab 3
  by Russell Schlup
  May 14, 2014
 */

#include <SPI.h>
#include <Ethernet.h>
#include "pitches.h"

String httpReq;
bool light = false;
String sensorLog;
String motionStart;
String measurement;
String button;
String action;
boolean currentLineIsBlank = true;
boolean startRequest = false;
boolean noReq = true;
long unsigned int lowIn;
boolean lockLow = true;
boolean takeLowTime;
int pirPin = 3;
int ledPin = 7;
String httpResp;

byte mac[] = { 
  0xAA, 0xBB, 0xBE, 0xEF, 0xFE, 0xED };

EthernetServer server(80);

void setup() {
  Serial.begin(9600);
 // Open serial communications and wait for port to open:
  pinMode(3, INPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  
  // start the Ethernet connection and the server:
  Ethernet.begin(mac);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  startRequest = false;
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        
        if(c == '?'){
          startRequest = true;
          noReq = false;
        }else if(c == ' '){
           startRequest = false;
        }
       
        if(startRequest){
          httpReq += c;
        }
       
        if(light){
          button = "Turn the system off.";
          action = "/?OFF";
          sense();
        }else{
          button = "Arm the system.";
          action = "/?ON";
          motionStart = "";
          measurement = "";
        }

        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          if(noReq){
            client.println();
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<head>");
            client.println("<link rel='stylesheet' href='//netdna.bootstrapcdn.com/bootstrap/3.1.1/css/bootstrap.min.css'><script type='text/javascript' src='http://code.jquery.com/jquery-2.1.1.min.js'></script><script type='text/javascript'>$.ajax({url: 'http://107.170.57.28/return.php', type: 'get', success: function (response){$('body').html(response)}});</script></head><body></body>");
            client.println("</head>");
            client.println("</html>");
          }else{
            client.println();
            client.print("{\"sensorLog\": \"");
            client.print(sensorLog);
            client.print(motionStart);
            client.print(measurement);
            client.print("\",\"action\": \"" + action + "\"}"); 
          }
          break;
        }

        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    
    if(httpReq == "?ON"){
       digitalWrite(7, HIGH);
       digitalWrite(3, LOW);
       sensorLog = ("Calibrating sensor <br /> Done <br /> SENSOR ACTIVE <br /> Motion Detected at: ");
       measurement = " sec";
       light = true;
     }else if(httpReq == "?OFF"){
       digitalWrite(7, LOW);
       sensorLog = ("System turned off");
       light = false;
     }else if(httpReq == "?PLAY"){
       play();
     }
     noReq = true;
     Serial.print("HTTPReq: ");
     Serial.print(httpReq);
     httpReq = "";
    // give the web browser time to receive the data
    delay(1);
    
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

void sense(){
  if(digitalRead(pirPin) == HIGH){
    if(lockLow){  
      //makes sure we wait for a transition to LOW before any further output is made:
      lockLow = false;
      motionStart = (String)(millis()/1000);
    }         
    takeLowTime = true;
  }

  if(digitalRead(pirPin) == LOW){

    if(takeLowTime){
      lowIn = millis();          //save the time of the transition from high to LOW
      takeLowTime = false;       //make sure this is only done at the start of a LOW phase
    }
     //if the sensor is low for more than the given pause, 
     //we assume that no more motion is going to happen
    if(!lockLow && millis() - lowIn > 1000){  
        //makes sure this block of code is only executed again after 
        //a new motion sequence has been detected
        lockLow = true;
    }
  }
}




// -------------------- functions
void play(){
  // notes in the melody:
  int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0, 

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0
};

  // note durations: 4 = quarter note, 8 = eighth note, etc.:
  int noteDurations[] = {
  12, 12, 12, 12, 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12, 

  12, 12, 12, 12,
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};
  
  for (int thisNote = 0; thisNote < 77; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(8, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}
