#ifndef MQ2_SENSOR_H
#define MQ2_SENSOR_H

#include "ModestIoT.h"

class Mq2Sensor : public Sensor {
private:
    unsigned long lastReadTime = 0;
    const long readInterval = 10000;

public:
    static const int MQ2_READING_EVENT_ID = 2;
    Mq2Sensor(int pin, EventHandler* handler);
    void init() override;
    void update() override;
};

#endif