#include <SPI.h>
#include <Ethernet.h>

// -------------------- pin for change --------------------//
int plugPin = 7;



// assign a MAC address for the ethernet controller.
// fill in your address here:
String nodeCheck;
boolean startReturn = false;
byte mac[] = { 
  0xAA, 0xBB, 0xCC, 0xEF, 0xFE, 0xED};
// fill in an available IP address on your network here,
// for manual configuration:
IPAddress ip(10,20,31,20);

// fill in your Domain Name Server address here:
IPAddress myDns(1,1,1,1);

// initialize the library instance:
EthernetClient client;

char server[] = "107.170.57.28";

unsigned long lastConnectionTime = 0;          // last time you connected to the server, in milliseconds
boolean lastConnected = false;                 // state of the connection last time through the main loop
const unsigned long postingInterval = 60*1000;  // delay between updates, in milliseconds

void setup() {
  // start serial port:
  Serial.begin(9600);
  pinMode(plugPin, OUTPUT);
  // give the ethernet module time to boot up:
  delay(1000);
  // start the Ethernet connection using a fixed IP address and DNS server:
  Ethernet.begin(mac, ip);
  // print the Ethernet board/shield's IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);

    if(c == '#'){
      startReturn = true;
    }else if(c == '/n'){
       startReturn = false;
    }
   
    if(startReturn){
      nodeCheck += c;
      if(c!='#'){
        startReturn = false;
      }
    }
    
  }
  
  if(nodeCheck == "#1"){
    digitalWrite(plugPin, HIGH);
    Serial.println("Coffee On");
    nodeCheck = "";
  }else if(nodeCheck == "#0"){
    digitalWrite(plugPin, LOW);
    Serial.println("Coffee Off");
    nodeCheck = "";
  }
  

  // if there's no net connection, but there was one last time
  // through the loop, then stop the client:
  if (!client.connected() && lastConnected) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }

  // if you're not connected, and ten seconds have passed since
  // your last connection, then connect again and send data:
  if(!client.connected()) {
    httpRequest();
  }
  
  // store the state of the connection for next time through
  // the loop:
  lastConnected = client.connected();
}

// this method makes a HTTP connection to the server:
void httpRequest() {
  // if you get a connection, report back via serial:
  if (client.connect(server, 5000)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET / HTTP/1.1");
    client.println("Host: www.google.com");
    client.println("Connection: close");
    client.println();
    delay(10000);
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
    nodeCheck = "";
  }
}




