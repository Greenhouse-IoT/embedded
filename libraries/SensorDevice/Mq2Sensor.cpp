#include "Mq2Sensor.h"

Mq2Sensor::Mq2Sensor(int pin, EventHandler* handler)
    : Sensor(pin, handler) {}

void Mq2Sensor::init() {
    pinMode(pin, INPUT);
}

void Mq2Sensor::update() {
    if (millis() - lastReadTime > readInterval) {
        lastReadTime = millis();
        int co2_analog = analogRead(pin);
        int co2_ppm = map(co2_analog, 0, 4095, 350, 2000); // Mapeo simple
        Event event(MQ2_READING_EVENT_ID);
        event.setData(co2_ppm);
        on(event);
    }
}