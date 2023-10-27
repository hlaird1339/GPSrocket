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
int i = 1; /// test
String evenness = "eve";
unsigned long lastTransmitTime = 0;

void setup() {
  Serial.begin(9600); // Initialize USB Serial
  delay(1000);
  
  LoRaSerial.begin(9600); // Initialize Software Serial

  pinMode(LED_BUILTIN, OUTPUT);
  
}

void loop() {

  if (millis() - lastTransmitTime >= 3000) {
    lastTransmitTime = millis();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    if (i%2 == 0) {
      Serial.println(i);
      evenness = "eve";
    }
    else{
      Serial.println(i);
      evenness = "odd";
    }
    
    String flying = "AT+SEND=1,8,Hello"+ evenness;
    Serial.println(flying);
    LoRaSerial.println(flying); // Send data

    digitalWrite(LED_BUILTIN, LOW); // Turn off sender LED
    i = i+1;
  }

  /*
  if (millis() - lastTransmitTime >= 1000) {
    lastTransmitTime = millis();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    String flying = "AT+SEND=1,5,Hello";

    LoRaSerial.println(flying); // Send data

    digitalWrite(LED_BUILTIN, LOW); // Turn off sender LED
  }
  */
}
 
