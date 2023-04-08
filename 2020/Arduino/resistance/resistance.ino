int R_fixed = 10000; // change to real value
double R_thermistor, total;

void setup() {
  Serial.begin(9600);
  //analogReference(EXTERNAL);
}

void loop() {
  total = 0; // reset
  for (int i = 0; i < 10; i++) total += analogRead(1); // 10 readings
  R_thermistor = R_fixed * total / (10230 - total);
 
  // remove printing and delay after testing
  Serial.print("Thermistor resistance: ");
  Serial.println(R_thermistor);


  delay(1000);
}
