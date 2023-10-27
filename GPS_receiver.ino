#include <SoftwareSerial.h>

#define RX 3
#define TX 2
//GPS_receiver | Arduino IDE 2.2.1

SoftwareSerial LoRaSerial(RX, TX); // RX, TX
unsigned long oldUpdate = 0.0;
unsigned long newUpdate = 0.0;

void setup() {
  Serial.begin(9600); // Initialize USB Serial
  delay(1000);
  
  LoRaSerial.begin(9600); // Initialize Software Serial

  pinMode(LED_BUILTIN, OUTPUT);
    
}

void loop() {
  if(LoRaSerial.available()) {
    String incommingData = LoRaSerial.readStringUntil('\n');
    Serial.println(incommingData);

    //transmission times
    newUpdate = millis();
    Serial.print("Time from last update[s]: ");
    Serial.println((newUpdate-oldUpdate)/1000.0);
    oldUpdate = newUpdate;

    // checking if incoming GPS has been set up yet
    if(incommingData.indexOf("GPS BAD") != -1){
      Serial.println("GPS signal not yet found");
    }
    else{
      //Decoding incoming data
      String location = incommingData;
      int start = location.indexOf(",",7) + 1;
      //altitude
      int altIndex = location.indexOf(".") + 2;
      float altitude = (location.substring(start, altIndex)).toFloat();
      Serial.print("Altitude[m]: ");
      Serial.println(altitude);
      //latitude
      int latIndex = location.indexOf(".", altIndex) + 8;
      String latitude = (location.substring(altIndex,latIndex));
      Serial.print("Latitude: ");
      Serial.println(latitude);
      //longitude
      int longIndex = location.indexOf(".", latIndex) + 8;
      String longitude = (location.substring(latIndex,longIndex));
      Serial.print("Longitude: ");
      Serial.println(longitude);
    }
  }
}
