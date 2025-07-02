#include "ActuatorDevice.h"

ActuatorDevice device;

void setup() {
  Serial.begin(115200);
  device.init();
}

void loop() {
  device.loop();
}