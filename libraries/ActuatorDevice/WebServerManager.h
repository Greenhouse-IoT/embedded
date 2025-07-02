#ifndef WEBSERVER_MANAGER_H
#define WEBSERVER_MANAGER_H

#include <WebServer.h>
#include <ArduinoJson.h>
#include "CommandHandler.h" // Para poder enviar comandos

class WebServerManager {
private:
    WebServer server;
    CommandHandler* commandHandler; // El dispositivo al que enviará comandos

    void handleRequest();

public:
    WebServerManager(CommandHandler* handler);
    void init(const char* ssid, const char* pass, const char* endpoint);
    void handleClient();
};

#endif