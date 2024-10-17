#include <ESP8266WiFi.h>
//#include <ESPAsyncWebServer.h>

#include "IRremote.hpp"

// Replace with your network credentials
const char *ssid = "wi-fi ssid";
const char *password = "wi-fi password";

const int irReceiverPin = 5; // D5
const int irLedPin = 7;  // D7

const int buttonPin = 6; // D6

unsigned long previousMillis = 0UL;
unsigned long interval = 100UL; // 100 milliseconds

void setup() {
  
  Serial.begin(115200);
  IrReceiver.begin(irReceiverPin, ENABLE_LED_FEEDBACK);
  
  pinMode ( irLedPin, OUTPUT);
  pinMode ( irReceiverPin, INPUT);
  pinMode ( buttonPin, INPUT);
}

void loop() {

  if (IrReceiver.decode()){
    
    unsigned long int decCode = IrReceiver.decodedIRData.command;
    Serial.println(decCode, HEX);

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > interval){
      
      if (decCode == 0xA){ //Write decoded hex value and add conditions to another values
        
        digitalWrite(irLedPin, decCode);
      }

      previousMillis = currentMillis;
    }
    
    IrReceiver.resume(); 
  }
}
