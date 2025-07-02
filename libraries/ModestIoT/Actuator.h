/**
 * @file Actuator.h
 * @brief Declares the Actuator base class.
 * @author Angel Velasquez
 * @date March 22, 2025
 */
#ifndef ACTUATOR_H
#define ACTUATOR_H

#include "CommandHandler.h"
#include <Arduino.h>

class Actuator {
protected:
    int pin;
    CommandHandler* handler;

public:
    Actuator(int actuatorPin, CommandHandler* commandHandler)
        : pin(actuatorPin), handler(commandHandler) {}

    virtual void handle(Command command) {
        if (handler) {
            handler->handle(command);
        }
    }

    virtual void init() = 0;
};

#endif // ACTUATOR_H