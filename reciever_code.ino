/*************************************************************************************************
 *  Created By: Tauseef Ahmad
 *  Created On: 28 June, 2023
 *  
 *  YouTube Video: https://youtu.be/LrEEN4Ji-Ec
 *  My Channel: https://www.youtube.com/@AhmadLogs
 ***********************************************************************************************/

#include <SoftwareSerial.h>

#define RX 3
#define TX 2
SoftwareSerial LoRaSerial(RX, TX); // RX, TX

unsigned long lastTransmitTime = 0;

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
    
    if(incommingData.indexOf("HELLO")){
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
    }
    
  }
}