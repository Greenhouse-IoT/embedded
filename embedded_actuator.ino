#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino_JSON.h>

// --- CONFIGURACIÓN DE WIFI ---
const char* WIFI_SSID = "";
const char* WIFI_PASS = "";

// --- CONFIGURACIÓN DE PINES Y DISPOSITIVOS ---
#define SERVO_PIN 15
// Dirección I2C de la pantalla LCD. La 0x27 es la más común.
#define LCD_I2C_ADDR 0x27

// --- INICIALIZACIÓN DE OBJETOS ---
WebServer server(80);
Servo myServo;
LiquidCrystal_I2C lcd(LCD_I2C_ADDR, 16, 2);

/**
 * @brief Actualiza la pantalla LCD con las lecturas y sus indicadores individuales.
 */
void updateLcd(float temp, String tempAction, float hum, String humAction, int co2, String co2Action) {
  lcd.clear();
  
  // --- Fila 1: Temperatura y Humedad ---
  lcd.setCursor(0, 0);
  String line1 = "T:" + String(temp, 1) + tempAction + " H:" + String(hum, 1) + humAction;
  lcd.print(line1);

  // --- Fila 2: CO2 ---
  lcd.setCursor(0, 1);
  String line2 = "CO2: " + String(co2) + "ppm " + co2Action;
  lcd.print(line2);
}

/**
 * @brief Maneja la petición HTTP para activar actuadores.
 */
void handleActuators() {
  if (!server.hasArg("plain")) {
    server.send(400, "text/plain", "Bad Request: No JSON payload");
    return;
  }

  String jsonBody = server.arg("plain");
  Serial.println("Payload recibido: " + jsonBody);

  JSONVar jsonData = JSON.parse(jsonBody);

  if (JSON.typeof(jsonData) == "undefined") {
    server.send(400, "text/plain", "Bad Request: Invalid JSON format");
    return;
  }

  // Extraer los datos y las acciones individuales del JSON
  float temp = (double)jsonData["temperature"];
  String tempAction = (const char*)jsonData["temp_action"];
  float hum = (double)jsonData["humidity"];
  String humAction = (const char*)jsonData["hum_action"];
  int co2 = (int)jsonData["co2"];
  String co2Action = (const char*)jsonData["co2_action"];
  String servoAction = (const char*)jsonData["servo_action"];

  // Actualizar la pantalla LCD con todos los datos
  updateLcd(temp, tempAction, hum, humAction, co2, co2Action);
  
  // Actuar sobre el servo basado en la acción general
  if (servoAction == "+") {
    Serial.println("Accion de servo '+', activando.");
    myServo.write(90); 
    delay(1000);
    myServo.write(0);
  } else {
    Serial.println("Accion de servo '-', no se activa.");
  }
  
  server.send(200, "text/plain", "Actuator command received successfully.");
}

// --- Las funciones setup() y loop() permanecen idénticas a la versión anterior ---

void setup() {
  Serial.begin(115200);
  
  myServo.attach(SERVO_PIN);
  myServo.write(0);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Conectando WiFi");
  
  Serial.print("Conectando a ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED && attempt < 20) {
    delay(500);
    Serial.print(".");
    lcd.setCursor(attempt % 16, 1);
    lcd.print(".");
    attempt++;
  }

  lcd.clear();
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi conectado!");
    Serial.print("Direccion IP: ");
    Serial.println(WiFi.localIP());
    lcd.setCursor(0, 0);
    lcd.print("Conectado!");
    lcd.setCursor(0, 1);
    lcd.print(WiFi.localIP());
  } else {
    Serial.println("\nFallo la conexion WiFi.");
    lcd.setCursor(0, 0);
    lcd.print("Error WiFi");
  }

  delay(2000);

  server.on("/activate-servo", HTTP_POST, handleActuators);
  
  server.begin();
  Serial.println("Servidor web iniciado.");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Esperando datos");
}

void loop() {
  server.handleClient();
}