/**
 * @file Device.h
 * @brief Declares the Device interface.
 * @author Angel Velasquez
 * @date March 22, 2025
 */
#ifndef DEVICE_H
#define DEVICE_H

#include "EventHandler.h"
#include "CommandHandler.h"

class Device : public EventHandler, public CommandHandler {
public:
    virtual void on(Event event) override = 0;
    virtual void handle(Command command) override = 0;
    virtual ~Device() = default;
};

#endif // DEVICE_H