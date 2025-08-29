#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>  // Use Adafruit_BME280.h if using BME280
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Tars";
const char* password = "sam_1983";

Adafruit_BMP280 bmp; // Use Adafruit_BME280 if using BME280
WebServer server(80);

// Function to serve web page
void handleRoot() {
    String page = "<html><head><title>ESP32 Weather Station</title>"
    "<style>body {text-align: center; font-family: Arial;}</style></head><body>"
    "<h2>ESP32 BMP280 Sensor</h2>"
    "<p>Temperature: " + String(bmp.readTemperature()) + " °C</p>"
    "<p>Pressure: " + String(bmp.readPressure() / 100.0) + " hPa</p>";
    
    #ifdef USE_BME280  // If using BME280 for humidity
        page += "<p>Humidity: " + String(bmp.readHumidity()) + " %</p>";
    #endif
    
    page += "</body></html>";
    server.send(200, "text/html", page);
}

void setup() {
    Serial.begin(115200);
    Wire.begin();

    Serial.print("Connecting to WiFi");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi!");
    Serial.print("ESP32 IP Address: ");
    Serial.println(WiFi.localIP());

    if (!bmp.begin(0x76)) { // BMP280/BME280 default I2C address
        Serial.println("BMP280 not found! Check wiring.");
        while (1);
    }
    Serial.println("BMP280 Initialized");

    server.on("/", handleRoot);
    server.begin();
}

void loop() {
    server.handleClient();
    Serial.print(bmp.readTemperature());
    Serial.print(" ");
    Serial.print(bmp.readPressure() / 100.0);
    Serial.println();
    delay(1000);
}