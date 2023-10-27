#include <SoftwareSerial.h>
#include <LoRa.h>
#include <TinyGPS++.h>

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the LoRa device
SoftwareSerial LoRaSerial(3, 2); // RX, TX
// The serial connection to the GPS device
SoftwareSerial ss(4, 5); // RX, TX

unsigned long lastTransmitTime = 0;
int update = 0;
String preSet = "AT+SEND=1,7,GPS BAD";

void setup() {
  Serial.begin(9600); // Initialize USB Serial
  LoRaSerial.begin(9600);
  delay(1000);
  ss.begin(9600);
  delay(1000);
  
  pinMode(LED_BUILTIN, OUTPUT);
    
}

void loop() {
  // reading gps data
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      String latitude = String(gps.location.lat(),7);
      String longitude = String(gps.location.lng(),7);
      String altitude = String(gps.altitude.meters(),1);
      String localArea = altitude+latitude+longitude;

      // data on what to send and how long it is
      String z = String(localArea.length());
      z = z+",";
      preSet = "AT+SEND=1,"+z+localArea;
      Serial.println(preSet);   
    }  
  }
  
  if (millis() - lastTransmitTime >= 1000) {
    lastTransmitTime = millis();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    String flying = "AT+SEND=1,5,Hello";
    Serial.println(preSet+"   hello"); 
    LoRaSerial.println(preSet); // Send data

    digitalWrite(LED_BUILTIN, LOW); // Turn off sender LED
  }

    
    /*
    lastTransmitTime = millis();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    String flying = "AT+SEND=1,5,HELLO";

    LoRaSerial.println(flying); // Send data

    digitalWrite(LED_BUILTIN, LOW); // Turn off sender LED
    LoRaSerial.end();
    delay (400);
  
  

  //data transmission
  //LoRaSerial.listen();
  /*
  if (millis() - lastTransmitTime >= 1000) {
    lastTransmitTime = millis();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    String flying = "AT+SEND=1,5,HELLO";

    LoRaSerial.println(preset); // Send data

    digitalWrite(LED_BUILTIN, LOW); // Turn off sender LED
    Serial.println(preset);
  }
    //delay (1000);
  //LoRaSerial.stopListening();
  */

  /*
    if (millis() - lastTransmitTime >= 1000) {
    lastTransmitTime = millis();
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("here");
    
    Serial.println(gps.encode(gpsSerial.read()));
    Serial.println(gps.location.isUpdated());
    if (gps.location.isUpdated()){
      Serial.println("now");
      String latitude = String(gps.location.lat(),7);
      String longitude = String(gps.location.lng(),7);
      String altitude = String(gps.altitude.meters(),1);
      String localArea = altitude+latitude+longitude;

      String z = String(localArea.length());
      z = z+",";
      String preSet = "AT+SEND=1,"+z+localArea;
      //LoRaSerial.println(preSet);
      Serial.println(preSet);
      delay(1000);
    }


    //LoRaSerial.println("AT+SEND=2,12,recentPosition"); // Send data
    delay (100);
    digitalWrite(LED_BUILTIN, LOW); // Turn off sender LED
  }
  */
}
 

