#ifndef ACTUATOR_DEVICE_H
#define ACTUATOR_DEVICE_H

#include "ModestIoT.h"
#include "ServoActuator.h"
#include "LcdActuator.h"
#include "WebServerManager.h"

class ActuatorDevice : public Device {
private:
    ServoActuator servo;
    LcdActuator lcd;
    WebServerManager webServer;

public:
    static const int SERVO_PIN = 15;

    ActuatorDevice();
    void init();
    void loop();
    void on(Event event) override;
    void handle(Command command) override;
};

#endif