#ifndef NETWORKS_CLIENT_H
#define NETWORKS_CLIENT_H

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

class NetworksClient {
private:
    const char* ssid;
    const char* password;
    const char* serverUrl;
    const char* deviceId;
    const char* apiKey;
    HTTPClient http;

public:
    NetworksClient(const char* s, const char* p, const char* url, const char* devId, const char* key);
    void init();
    void sendReadings(float temp, float hum, int co2);
};

#endif