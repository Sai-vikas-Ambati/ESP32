#include <BluetoothSerial.h>
BluetoothSerial bt;
void setup() {
  Serial.begin(9600);
  bt.begin("ESP32");
}

void loop() {
  if(bt.available())
  {
    String x = bt.readStringUntil('\n');
    Serial.println(x+'\n');  }
}
