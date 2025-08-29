#include <Wire.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

const char* ssid = "Tars";  // Your WiFi SSID
const char* pwd = "sam_1983";   // Your WiFi Password

WebServer server(80);
Adafruit_MPU6050 mpu;  // Create MPU6050 instance

void handleRoot() {
    String page =  
    "<html><head><title>ESP32 MPU6050 Data</title>"
    "<script>"
    "function updateData() {"
    "  fetch('/data')"
    "  .then(response => response.text())"
    "  .then(data => { document.getElementById('mpuData').innerText = data; });"
    "  setTimeout(updateData, 500);"
    "}"
    "window.onload = updateData;"
    "</script>"
    "<style>body {text-align: center; font-family: Arial;}</style></head><body>"
    "<h2>ESP32 MPU6050 Sensor Data</h2>"
    "<p>Accelerometer & Gyroscope: <span id='mpuData'>Loading...</span></p>"
    "</body></html>";

    server.send(200, "text/html", page);
}

void handleData() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    String sensorData = "Ax: " + String(a.acceleration.x) + ", Ay: " + String(a.acceleration.y) + ", Az: " + String(a.acceleration.z) + 
                        ", Gx: " + String(g.gyro.x) + ", Gy: " + String(g.gyro.y) + ", Gz: " + String(g.gyro.z);

    server.send(200, "text/plain", sensorData);
}

void setup() {
    Serial.begin(115200);
    Wire.begin();
    
    if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050 chip!");
        while (1);
    }
    Serial.println("MPU6050 Initialized.");
    
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

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    Serial.print(a.acceleration.x);
    Serial.print(" ");
    Serial.print(a.acceleration.y);
    Serial.print(" ");
    Serial.print(a.acceleration.z);
    Serial.print(" ");
    Serial.print(g.gyro.x);
    Serial.print(" ");
    Serial.print(g.gyro.y);
    Serial.print(" ");
    Serial.println(g.gyro.z);

    delay(500);
}
