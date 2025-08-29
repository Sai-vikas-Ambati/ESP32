void setup() {
  pinMode(33 , OUTPUT);
  pinMode(4 , OUTPUT);

  digitalWrite(33 , LOW);
  digitalWrite(4 , LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(33 , HIGH);
  digitalWrite(4 , LOW);

  delay(1000);

  digitalWrite(33 , LOW);
  digitalWrite(4 , HIGH);

  delay(1000);
}
