#include "SensorDevice.h"

SensorDevice::SensorDevice()
    : dhtSensor(DHT_PIN, this),
      mq2Sensor(MQ2_PIN, this),
      NetworksClient("wifiuser", "wifipassword", "edge-endpoint", "deviceId", "apiKey") {}

void SensorDevice::init() {
    NetworksClient.init();
    dhtSensor.init();
    mq2Sensor.init();
}

void SensorDevice::handle(Command command) {
    // Este dispositivo no maneja comandos, solo envía datos.
}

void SensorDevice::on(Event event) {
    if (event.id == DhtSensor::DHT_READING_EVENT_ID) {
        DhtData data = event.getData<DhtData>();
        lastTemperature = data.temperature;
        lastHumidity = data.humidity;
        tempReady = true;
    } else if (event.id == Mq2Sensor::MQ2_READING_EVENT_ID) {
        lastCo2 = event.getData<int>();
        co2Ready = true;
    }

    if (tempReady && co2Ready) {
        Serial.println("Enviando datos de sensores al servidor...");
        NetworksClient.sendReadings(lastTemperature, lastHumidity, lastCo2);
        tempReady = false;
        co2Ready = false;
    }
}

void SensorDevice::loop() {
    dhtSensor.update();
    mq2Sensor.update();
}