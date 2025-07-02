#ifndef SENSOR_DEVICE_H
#define SENSOR_DEVICE_H

#include "ModestIoT.h"
#include "DhtSensor.h"
#include "Mq2Sensor.h"
#include "NetworksClient.h"

class SensorDevice : public Device {
private:
    DhtSensor dhtSensor;
    Mq2Sensor mq2Sensor;
    NetworksClient NetworksClient;

    float lastTemperature = 0.0f;
    float lastHumidity = 0.0f;
    int lastCo2 = 0;
    bool tempReady = false;
    bool co2Ready = false;

public:
    static const int DHT_PIN = 4;
    static const int MQ2_PIN = 32;

    SensorDevice();
    void init();
    void loop();
    void on(Event event) override;
    void handle(Command command) override;
};

#endif