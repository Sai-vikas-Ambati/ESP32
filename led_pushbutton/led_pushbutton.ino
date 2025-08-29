int s;

void setup() {
  pinMode(33 , OUTPUT);
  pinMode(4 , OUTPUT);

  pinMode(32 , INPUT);

  digitalWrite(33 , LOW);
  digitalWrite(4 , LOW);
}

void loop() {
  s = digitalRead(32);

  if(s == 1)
  {
    digitalWrite(33 , HIGH);
    digitalWrite(4 , LOW);

    delay(100);

    digitalWrite(4 , HIGH);
    digitalWrite(33 , LOW);

    delay(100);
  }

  else if(s == 0)
  {
    digitalWrite(33 , HIGH);
    digitalWrite(4 , HIGH);

    delay(100);

    digitalWrite(4 , LOW);
    digitalWrite(33 , LOW);

    delay(100);
  }
}
