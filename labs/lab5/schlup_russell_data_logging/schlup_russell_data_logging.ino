#include <SPI.h>
#include <Ethernet.h>
#include <HttpClient.h>
#include <Xively.h>

// MAC address for your Ethernet shield
byte mac[] = { 0xAA, 0xBB, 0xCC, 0xEF, 0xFE, 0xED };

// Your Xively key to let you upload data
char xivelyKey[] = "djBr2cpg1hnc5N5h3qoFXP4pDlKsed2aYO0Exm14zVtGbyCx";

// Analog pin which we're monitoring (0 and 1 are used by the Ethernet shield)
int sensorPin = 2;
int ldrVal = 0;
int pirVal;

// Define the strings for our datastream IDs
char sensorId[] = "FS-4A_107_Temp";
char pirID[] = "FS-4A_107_Movement";
char ldrID[] = "FS-4A_107_Lighting";

XivelyDatastream datastreams[] = {
  XivelyDatastream(sensorId, strlen(sensorId), DATASTREAM_FLOAT),
  XivelyDatastream(pirID, strlen(pirID), DATASTREAM_FLOAT),
  XivelyDatastream(ldrID, strlen(ldrID), DATASTREAM_FLOAT),
};
// Finally, wrap the datastreams into a feed
XivelyFeed feed(1553462817, datastreams, 3 /* number of datastreams */);

EthernetClient client;
XivelyClient xivelyclient(client);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(6, INPUT);
  digitalWrite(6, LOW);
  
  Serial.println("Starting single datastream upload to Xively...");
  Serial.println();

  while (Ethernet.begin(mac) != 1)
  {
    Serial.println("Error getting IP address via DHCP, trying again...");
    delay(15000);
  }
}

void loop() {
  
  ldrVal = analogRead(0);    // read the input pin
  
  if(digitalRead(6) == HIGH){
    digitalWrite(13, HIGH);
    Serial.println("detected movement");
    pirVal = 1;
  }else{
    digitalWrite(13, LOW);
    pirVal = 0;
  }
  
  int sensorValue = GetTemp();
  datastreams[0].setFloat(sensorValue);
  datastreams[1].setFloat(pirVal);
  datastreams[2].setFloat(ldrVal);

  Serial.print("Read sensor value ");
  Serial.println(datastreams[0].getFloat());
  Serial.println(datastreams[1].getInt());

  Serial.println("Uploading it to Xively");
  int ret = xivelyclient.put(feed, xivelyKey);
  Serial.print("xivelyclient.put returned ");
  Serial.println(ret);

  Serial.println();
  delay(15000);
}

double GetTemp(void)
{
  unsigned int wADC;
  double t;

  ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
  ADCSRA |= _BV(ADEN);  // enable the ADC

  delay(20);            // wait for voltages to become stable.

  ADCSRA |= _BV(ADSC);  // Start the ADC

  // Detect end-of-conversion
  while (bit_is_set(ADCSRA,ADSC));

  // Reading register "ADCW" takes care of how to read ADCL and ADCH.
  wADC = ADCW;

  // The offset of 324.31 could be wrong. It is just an indication.
  t = (wADC - 324.31 ) / 1.22;

  // The returned temperature is in degrees Celcius.
  return ((t*1.8+32)-14);
}
