#include "ServoActuator.h"

ServoActuator::ServoActuator(int pin, CommandHandler* handler)
    : Actuator(pin, handler) {}

void ServoActuator::init() {
    servoMotor.attach(pin);
    servoMotor.write(0); // Posición inicial cerrada
}

void ServoActuator::handle(Command command) {
    if (command.id == SERVO_OPEN_COMMAND_ID) {
        Serial.println("Abriendo servo...");
        servoMotor.write(90);
    } else if (command.id == SERVO_CLOSE_COMMAND_ID) {
        Serial.println("Cerrando servo...");
        servoMotor.write(0);
    }
}