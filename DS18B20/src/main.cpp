#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const int oneWireBus = D3;

OneWire oneWire(oneWireBus);

DallasTemperature DS18B20(&oneWire);

DeviceAddress deviceAddress; 
bool sensorFound = false;

void setup() {
  Serial.begin(115200);

  DS18B20.begin();

  Serial.println("\nTemperature Application");

  if (DS18B20.getAddress(deviceAddress, 0)) {
    sensorFound = true;

    Serial.print("Found DS18B20 sensor with address: ");

    for (int i = 0; i < 8; i++){
      if (deviceAddress[i] < 16) {
        Serial.print("0");
      }

      Serial.print(deviceAddress[i], HEX);

    }

    Serial.println();
    
  } else {
    Serial.println("No DS18B20 temperature sensors are installed!");
  }
  
}

void loop() {

  if (!sensorFound) {
    delay(1000);
    return;
  }

  float fTemp;
  
  DS18B20.requestTemperatures();

  fTemp = DS18B20.getTempCByIndex(0);


  if (fTemp < 10){
    Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or cold!");
  } 
  if (fTemp >= 10 && fTemp < 15){
    Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or cool.");
  }
  if (fTemp >= 15 && fTemp < 25){
    Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or perfect.");
  }
  if (fTemp >= 25 && fTemp < 30){
    Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or warm.");
  }
  if (fTemp >= 30 && fTemp <= 35){
    Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or hot.");
  }
  if (fTemp >35){
    Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or too hot!");
  }
  
  delay(5000);
}

