#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

#define DHTPIN 4       // GPIO4 for DHT11 data pin
#define DHTTYPE DHT11  // Define sensor type as DHT11

const char* ssid = "Tars";  // Your WiFi SSID
const char* pwd = "sam_1983";  // Your WiFi Password

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

void handleRoot() {
    String page =
    "<html><head><title>ESP32 DHT11 Data</title>"
    "<script>"
    "function updateData() {"
    "  fetch('/data')"
    "  .then(response => response.text())"
    "  .then(data => { document.getElementById('sensorData').innerText = data; });"
    "  setTimeout(updateData, 2000);"
    "}"
    "window.onload = updateData;"
    "</script>"
    "<style>body {text-align: center; font-family: Arial;}</style></head><body>"
    "<h2>ESP32 DHT11 Sensor Data</h2>"
    "<p>Temperature & Humidity: <span id='sensorData'>Loading...</span></p>"
    "</body></html>";

    server.send(200, "text/html", page);
}

void handleData() {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
        server.send(500, "text/plain", "Sensor Error");
        return;
    }

    String sensorData = "Temperature: " + String(temperature) + " °C, Humidity: " + String(humidity) + " %";
    server.send(200, "text/plain", sensorData);
}

void setup() {
    Serial.begin(115200);
    dht.begin();

    WiFi.begin(ssid, pwd);
    Serial.print("Connecting to WiFi");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConnected to WiFi!");
    Serial.print("ESP32 IP Address: ");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.on("/data", handleData);
    server.begin();
}

void loop() {
    server.handleClient();

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (!isnan(temperature) && !isnan(humidity)) {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C, Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");
    } else {
        Serial.println("Failed to read from DHT sensor!");
    }

    delay(2000);
}
