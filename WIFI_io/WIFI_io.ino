#include <WiFi.h>

void setup()
{
  Serial.begin(115200); //starting a serial communication at a baud rate of 115200
  initWiFi(); //initializing WiFi
} 

void loop()
{
  //print anything
}

void initWiFi() //defining the function
{
  Serial.println("");
  WiFi.mode(WIFI_STA); //setting the mode of wifi to station(sta) mode so that the esp32 behaves as client and connet to an existing wifi network
  WiFi.begin("Tars" , "sam_1983"); //starting wifi with the appropriate username and password
  Serial.println("");
  Serial.println("Connecting to WiFi...");
  
  while(WiFi.status() != WL_CONNECTED) //a loop that waits untill the wifi is connected
  {
    Serial.println(".");
    delay(100);
  }

  Serial.println("");
  Serial.println(WiFi.localIP()); //after the connection is established print the local ip assigned to the device by dhcp
}