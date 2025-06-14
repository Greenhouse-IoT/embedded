#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <DHT.h>

// --- CONFIGURACIÓN DE RED ---
const char* WIFI_SSID = "";
const char* WIFI_PASS = "";

// Reemplaza con la IP de la PC donde corre el servicio de Python
const char* SERVER_IP = "http://192.168.1.44:3000"; 

// --- NUEVAS CONFIGURACIONES DE AUTENTICACIÓN ---
// Asegúrate que estos valores coincidan con los de tu base de datos IAM
const char* DEVICE_ID = "esp32-sensor-001";
const char* API_KEY   = "test-api-key-123";

// --- PINES DE SENSORES ---
#define DHT_PIN 13      // Pin digital para el DHT22
#define MQ2_PIN 34      // Pin analógico (ADC) para el MQ2

// --- INICIALIZACIÓN DE OBJETOS ---
#define DHT_TYPE DHT22
DHT dht(DHT_PIN, DHT_TYPE);
HTTPClient http;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Iniciar sensor DHT22
  dht.begin();

  // Conexión a la red WiFi
  Serial.print("Conectando a ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Esperar 10 segundos entre lecturas
  delay(10000);

  // --- LECTURA DE SENSORES ---
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // En Celsius
  int co2_analog = analogRead(MQ2_PIN);
  float co2ppm = co2_analog * (5.0 / 4095.0) * 1000; 
  
  // El MQ2 entrega un valor analógico. Para este ejemplo, usaremos el valor crudo.
  // En un caso real, deberías calibrar el sensor para convertir este valor a PPM.
  int co2_value = co2ppm; 

  // Validar lecturas del DHT22
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Error al leer del sensor DHT!");
    return; // Salir de esta iteración si hay error
  }

  Serial.printf("Lectura: Temp=%.2f°C, Hum=%.2f%%, CO2(Analog)=%d\n", temperature, humidity, co2_value);

  // --- PREPARAR Y ENVIAR DATOS AL SERVIDOR (VERSIÓN ACTUALIZADA) ---
  String endpoint = String(SERVER_IP) + "/api/v1/greenhouse/sensor-readings";
  
  // 1. Crear el objeto JSON (solo con los datos y el device_id)
  StaticJsonDocument<256> doc;
  doc["temperature"] = temperature;
  doc["humidity"] = humidity;
  doc["co2"] = co2_value;
  doc["device_id"] = DEVICE_ID;

  String jsonPayload;
  serializeJson(doc, jsonPayload);

  // 2. Iniciar la petición HTTP
  http.begin(endpoint);
  
  // 3. Añadir las cabeceras (Content-Type y la nueva X-API-Key)
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-API-Key", API_KEY);

  // 4. Enviar la petición POST
  int httpResponseCode = http.POST(jsonPayload);

  // 5. Procesar la respuesta
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.print("Código de respuesta HTTP: ");
    Serial.println(httpResponseCode);
    Serial.print("Respuesta del servidor: ");
    Serial.println(response);
  } else {
    Serial.print("Error en la petición POST. Código: ");
    Serial.println(httpResponseCode);
  }

  http.end(); // Liberar recursos
}