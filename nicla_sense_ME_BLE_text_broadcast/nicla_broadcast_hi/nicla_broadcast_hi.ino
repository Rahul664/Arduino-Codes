#include "Nicla_System.h"
#include <ArduinoBLE.h>

BLEService messageService("19b10000-0000-537e-4f6c-d104768a1214");
BLECharacteristic messageChar("19b10000-2000-537e-4f6c-d104768a1214", 
                              BLERead | BLENotify, 20);  // 20 bytes buffer

bool wasConnected = false;
unsigned long lastSendTime = 0;

void setup() {
  Serial.begin(115200);
  nicla::begin();
  nicla::leds.begin();
  nicla::leds.setColor(green);

  if (!BLE.begin()) {
    Serial.println("BLE init failed!");
    while (1);
  }
  
  BLE.setLocalName("XYZNicla");
  BLE.setDeviceName("XYZNicla");
  messageService.addCharacteristic(messageChar);
  BLE.addService(messageService);
  BLE.advertise();
}

void loop() {
  BLEDevice central = BLE.central();

  if (central && central.connected()) {
    if (!wasConnected) {
      Serial.print("Connected to: ");
      Serial.println(central.address());
      nicla::leds.setColor(blue);
      wasConnected = true;
    }

    // Send at 1Hz (1000ms interval)
    if (messageChar.subscribed() && millis() - lastSendTime >= 1000) {
      const char* msg = "Hi";
      messageChar.writeValue(msg);
      lastSendTime = millis();
    }
    
  } else if (wasConnected) {
    Serial.println("Disconnected. Advertising...");
    nicla::leds.setColor(green);
    wasConnected = false;
    BLE.advertise();  // Only restart advertising
  }

  BLE.poll();
}