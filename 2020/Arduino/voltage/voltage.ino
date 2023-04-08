void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Enternal: ");
  Serial.println(analogRead(0)/1023.0, 7);
  Serial.print("Internal: ");
  Serial.println(analogRead(1)/1023.0, 7);
  Serial.println();
  delay(2000);
}
