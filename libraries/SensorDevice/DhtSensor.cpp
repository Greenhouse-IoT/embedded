#include "DhtSensor.h"

DhtSensor::DhtSensor(int pin, EventHandler* handler)
    : Sensor(pin, handler), dht(pin, DHT22) {}

void DhtSensor::init() {
    dht.begin();
}

void DhtSensor::update() {
    if (millis() - lastReadTime > readInterval) {
        lastReadTime = millis();
        DhtData data = {dht.readTemperature(), dht.readHumidity()};

        if (!isnan(data.temperature) && !isnan(data.humidity)) {
            Event event(DHT_READING_EVENT_ID);
            event.setData(data);
            on(event);
        }
    }
}