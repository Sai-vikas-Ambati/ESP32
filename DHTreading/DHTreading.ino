#include <DHT.h>
DHT dht(13 , DHT11); //creating an object with the pin and DHTTYPE

void setup()
{
  Serial.begin(9600); //initializing a serial connection at 9600 baud rate
  dht.begin(); //initializing dht
}

void loop()
{
  float h = dht.readHumidity(); //reading the humidity
  float t1 = dht.readTemperature(); //reading temperature(celcius)
  float t2 = dht.readTemperature(true); //reading temperature(Farenheit)

  Serial.print("Humidity : ");
  Serial.println(h);

  Serial.print("Temperature(c) : ");
  Serial.println(t1);

  Serial.print("Temperatur(f) : ");
  Serial.println(t2);

  delay(1000);
}