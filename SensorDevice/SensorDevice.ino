#include "SensorDevice.h"

SensorDevice device;

void setup() {
  Serial.begin(115200);
  device.init();
}

void loop() {
  device.loop();
}