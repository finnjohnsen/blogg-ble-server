#include <Arduino.h>
#include <ArduinoBLE.h>

BLEService myService("e7b45330-61f5-403a-aa70-cf4293b019d8");
BLEStringCharacteristic myCharacteristic("953a2e20-5f52-4395-9b3d-102415feeab7", BLERead | BLEBroadcast, 2);
BLEDescriptor characterLabellDescriptor("2901", "Meningen med livet er...");


void connected(BLEDevice central) {
  Serial.print("Connected ");
  Serial.println(central.address());
  BLE.stopAdvertise();
}

void disconnected(BLEDevice central) {
  // central disconnected event handler
  Serial.print("Disconnected ");
  Serial.println(central.address());
  BLE.advertise();
}

void setup() {
  Serial.begin(115200);
  Serial.printf("Startup");

  if (!BLE.begin()) {
    Serial.println("Fikk ikke startet Bluetooth Low Energy :'( ");
    while (1);
  }

  BLE.setLocalName("Hoppsann");
  BLE.setAdvertisedService(myService);

  myService.addCharacteristic(myCharacteristic);

  myCharacteristic.addDescriptor(characterLabellDescriptor);
  myCharacteristic.setValue("42");

  BLE.addService(myService);

  BLE.setEventHandler(BLEConnected, connected);
  BLE.setEventHandler(BLEDisconnected, disconnected);
  
  BLE.advertise();
  Serial.println("Advertising ...");

}

void loop() {
    BLE.poll();
}

