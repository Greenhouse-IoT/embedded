/**
 * @file ActuatorDevice.cpp
 * @brief Implements the main device class for the Actuator unit.
 * @author ModestIoT Copilot
 * @date July 01, 2025
 */
#include "ActuatorDevice.h"

#include <WiFi.h>

ActuatorDevice::ActuatorDevice()
    : servo(SERVO_PIN, this),
      lcd(0x27, this),
      webServer(this) {}

void ActuatorDevice::init() {
    servo.init();
    lcd.init();
    webServer.init("wifiuser", "wifipassword", "/webserverendpoint");

    // Ahora 'WiFi' será reconocido gracias al #include <WiFi.h>
    LcdData ipData = {WiFi.localIP().toString(), "Esperando..."};
    Command cmd(LcdActuator::LCD_PRINT_COMMAND_ID);
    cmd.setData(ipData);
    handle(cmd);
}

void ActuatorDevice::on(Event event) {
    // Este dispositivo no reacciona a eventos, solo a comandos.
}

void ActuatorDevice::handle(Command command) {
    servo.handle(command);
    lcd.handle(command);
}

void ActuatorDevice::loop() {
    webServer.handleClient();
}