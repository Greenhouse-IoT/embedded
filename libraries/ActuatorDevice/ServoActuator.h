#ifndef SERVO_ACTUATOR_H
#define SERVO_ACTUATOR_H

#include "ModestIoT.h"
#include <ESP32Servo.h>

class ServoActuator : public Actuator {
private:
    Servo servoMotor;

public:
    static const int SERVO_OPEN_COMMAND_ID = 101;
    static const int SERVO_CLOSE_COMMAND_ID = 102;
    ServoActuator(int pin, CommandHandler* handler);
    void init() override;
    void handle(Command command) override;
};

#endif