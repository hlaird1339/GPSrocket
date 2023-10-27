/*
 * Rui Santos 
 * Complete Project Details https://randomnerdtutorials.com
 https://randomnerdtutorials.com/guide-to-neo-6m-gps-module-with-arduino/
 */
 
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 5; //TX is 4, RX is 5
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup(){
  Serial.begin(9600);
  ss.begin(GPSBaud);
}

void loop(){
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0){
    gps.encode(ss.read());
    //Serial.println(gps.encode(ss.read()));
    if (gps.location.isUpdated()){
      Serial.println(gps.encode(ss.read()));
      /*
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 8);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 8);
      */
      String latitude = String(gps.location.lat(),7);
      String longitude = String(gps.location.lng(),7);
      String altitude = String(gps.altitude.meters(),1);
      String localArea = altitude+latitude+longitude;

      // data on what to send and how long it is
      Serial.print(localArea.length());
      String z = String(localArea.length());
      z = z+",";
      Serial.println(z);
      String preSet = "AT+SEND=1,"+z+localArea;
      Serial.println(preSet);
      //String flying=localArea.length()+","+localArea;
      //Serial.println(flying);

      /*
      // how to decode the data once it comes back
      //altitude
      int altIndex = location.indexOf(".") + 2;
      Serial.println(location.substring(0,altIndex));
      //latitude
      int latIndex = location.indexOf(".", altIndex) + 8;
      Serial.println(location.substring(altIndex,latIndex));
      //longitude
      int longIndex = location.indexOf(".", latIndex) + 8;
      Serial.println(location.substring(latIndex,longIndex));
      */
    }
  }
}
