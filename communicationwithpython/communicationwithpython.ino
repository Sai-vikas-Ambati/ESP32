void setup() {
    Serial.begin(9600); // Start serial communication
    pinMode(, OUTPUT); // Example: control an LED
}

void loop() {
    if (Serial.available()) {
        char command = Serial.read(); // Read command from PC
        if (command == '1') {
            digitalWrite(13, HIGH); // Turn LED ON
        } else if (command == '0') {
            digitalWrite(13, LOW); // Turn LED OFF
        }
    }
}
