void setup()
{
  pinMode(39 , INPUT);
  pinMode(33 , OUTPUT);
  digitalWrite(33 , LOW);
}

void loop()
{
   int sensor_value = analogRead(39);

   if(sensor_value < 1024)
   {
      digitalWrite(33 , HIGH);
   }
   else if(sensor_value > 1024)
   {
    digitalWrite(33 , LOW);
   }
}
