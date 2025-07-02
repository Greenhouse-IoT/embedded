#include "NetworksClient.h"

NetworksClient::NetworksClient(const char* s, const char* p, const char* url, const char* devId, const char* key)
    : ssid(s), password(p), serverUrl(url), deviceId(devId), apiKey(key) {}

void NetworksClient::init() {
    Serial.print("Conectando a WiFi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConectado!");
}

void NetworksClient::sendReadings(float temp, float hum, int co2) {
    if (WiFi.status() == WL_CONNECTED) {
        String endpoint = String(serverUrl) + "/api/v1/greenhouse/sensor-readings";
        http.begin(endpoint);
        http.addHeader("Content-Type", "application/json");
        http.addHeader("X-API-Key", apiKey);

        StaticJsonDocument<200> doc;
        doc["temperature"] = temp;
        doc["humidity"] = hum;
        doc["co2"] = co2;
        doc["device_id"] = deviceId;

        String payload;
        serializeJson(doc, payload);

        int httpCode = http.POST(payload);
        if (httpCode > 0) {
            String response = http.getString();
            Serial.println("Código HTTP: " + String(httpCode));
            Serial.println("Respuesta: " + response);
        } else {
            Serial.println("Error en POST: " + String(httpCode));
        }
        http.end();
    }
}