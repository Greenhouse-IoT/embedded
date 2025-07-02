/**
 * @file WebServerManager.cpp
 * @brief Implements the web server management logic.
 * @author ModestIoT Copilot
 * @date July 01, 2025
 */
#include "WebServerManager.h"
#include "ServoActuator.h"
#include "LcdActuator.h"
#include <WiFi.h>

WebServerManager::WebServerManager(CommandHandler* handler)
    : server(80), commandHandler(handler) {}

void WebServerManager::init(const char* ssid, const char* pass, const char* endpoint) {
    Serial.print("Conectando a WiFi...");
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConectado!");
    Serial.println("IP: " + WiFi.localIP().toString());

    server.on(endpoint, HTTP_POST, [this](){ this->handleRequest(); });
    server.begin();
}

void WebServerManager::handleRequest() {
    if (!server.hasArg("plain")) {
        server.send(400, "text/plain", "Bad Request");
        return;
    }
    String body = server.arg("plain");
    StaticJsonDocument<256> doc;
    deserializeJson(doc, body);

    // Lógica para el servo
    String servoAction = doc["servo_action"];
    if (servoAction == "+") {
        commandHandler->handle(Command(ServoActuator::SERVO_OPEN_COMMAND_ID));
    } else {
        commandHandler->handle(Command(ServoActuator::SERVO_CLOSE_COMMAND_ID));
    }

    // Lógica para el LCD
    LcdData lcdData;
    lcdData.line1 = "T:" + doc["temperature"].as<String>() + doc["temp_action"].as<String>() + " H:" + doc["humidity"].as<String>() + doc["hum_action"].as<String>();
    lcdData.line2 = "CO2:" + doc["co2"].as<String>() + "ppm" + " " + doc["co2_action"].as<String>();
    Command lcdCmd(LcdActuator::LCD_PRINT_COMMAND_ID);
    lcdCmd.setData(lcdData);
    commandHandler->handle(lcdCmd);

    server.send(200, "text/plain", "OK");
}

void WebServerManager::handleClient() {
    server.handleClient();
}