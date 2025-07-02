#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include "ModestIoT.h"
#include <DHT.h>

struct DhtData {
    float temperature;
    float humidity;
};

class DhtSensor : public Sensor {
private:
    DHT dht;
    unsigned long lastReadTime = 0;
    const long readInterval = 10000;

public:
    static const int DHT_READING_EVENT_ID = 1;
    DhtSensor(int pin, EventHandler* handler);
    void init() override;
    void update() override;
};

#endif