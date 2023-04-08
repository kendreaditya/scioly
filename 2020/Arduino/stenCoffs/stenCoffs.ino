const int ThermistorPin = 0, bluePin = 12, greenPin = 11, redPin = 10;
const int R_fixed = 20000, n = 3, delayTime = 200, i = 0;
double logR2, R2, T, total;
double A, B, C;

double blue1 = 20.01, blue2 = 40;    // Blue LED Ranges
double green1 = 40.01 , green2 = 100;   // Green LED Ranges
double red1 = 0, red2 = 20;      // Red LED  Ranges
  

void setup() {
  Serial.begin(9600);
  //analogReference(EXTERNAL);      // Uses 3.3v VDD


  pinMode(bluePin, OUTPUT);         // Enables digital output though pin
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  
  A = 1.02119*pow(10,-3);
  B = 2.22468*pow(10,-4);
  C = 1.33342*pow(10,-7);

}

void loop() {
      double res = volateToResistance(ThermistorPin), temperature = temp(res);
      Serial.print("Temperature: ");
      Serial.print(temperature,3);
      Serial.println(" C");

      Serial.print("Resistance: ");
      Serial.print(res, 1);
      Serial.println(" ohm");

      Serial.print("Voltage:");
      Serial.print((analogRead(ThermistorPin) * 5.015) / 1024.0, 4);
      Serial.println(" volts");
      Serial.println("----------------------------------");
      led(temperature);
      delay(1000);
}
double temp(double resis)
{
  logR2 = log(resis);
  T = (1.0 / (A + B*logR2 + C*logR2*logR2*logR2))- 273.15;
  return T;
}
double volateToResistance(int pin)
{
  total = 0; // reset
  for (int i = 0; i < 10000; i++) total += analogRead(pin);
  double R_thermistor = R_fixed * total / (10230000 - total);
  return R_thermistor;
}
void led(double temp)
{
  if(blue1 < temp && blue2 >= temp)
    digitalWrite(bluePin, HIGH);
  else
    digitalWrite(bluePin, LOW);

  if(green1 < temp && green2 > temp)
    digitalWrite(greenPin, HIGH);
  else
    digitalWrite(greenPin, LOW);
  
  if(red1 <= temp && red2 >= temp)
    digitalWrite(redPin, HIGH);  
  else
    digitalWrite(redPin, LOW);
}
