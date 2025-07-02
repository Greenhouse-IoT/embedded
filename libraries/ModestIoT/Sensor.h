/**
 * @file Sensor.h
 * @brief Declares the Sensor base class.
 * @author Angel Velasquez
 * @date March 22, 2025
 */
#ifndef SENSOR_H
#define SENSOR_H

#include "EventHandler.h"
#include <Arduino.h>

class Sensor {
protected:
    int pin;
    EventHandler* handler;

public:
    Sensor(int sensorPin, EventHandler* eventHandler)
        : pin(sensorPin), handler(eventHandler) {}

    virtual void on(Event event) {
        if (handler) {
            handler->on(event);
        }
    }

    virtual void init() = 0;
    virtual void update() = 0;
};

#endif // SENSOR_H