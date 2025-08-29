#include "BluetoothSerial.h"
BluetoothSerial bt;

void setup() {
  Serial.begin(115200);
  bt.begin("ESPWROOM");
  pinMode(33 , OUTPUT);
  pinMode(4 , OUTPUT);
}

void loop() {
  if(bt.available())
  {
    char x = bt.read();
    if(x == 'A')
    {
      for(int i=0 ; i<10 ; i++)
      {
        digitalWrite(33 , HIGH);
        delay(500);
        digitalWrite(33,LOW);
        delay(500);
        digitalWrite(4 , HIGH);
        delay(500);
        digitalWrite(4,LOW);
        delay(500);
      }
    }

    else if(x == 'B')
    {
      for(int i=0 ; i<10 ; i++)
      {
        digitalWrite(33 , HIGH);
        digitalWrite(4 , HIGH);
        delay(500);
        digitalWrite(33,LOW);
        digitalWrite(4,LOW);
        delay(500);
      }
    }
  }
}
