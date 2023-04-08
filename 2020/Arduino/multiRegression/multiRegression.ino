const int ThermistorPin = 0, bluePin = 13, greenPin = 12, redPin = 11;
const int R_fixed = 5973, n = 3, delayTime = 200, i = 0;
double logR2, R2, T, total;
double A, B, C;

double blue1 = -10, blue2 = 15;    // Blue LED Ranges
double green1 = 15.1 , green2 = 25;   // Green LED Ranges
double red1 = 25.1, red2 = 100;      // Red LED  Ranges
  

void setup() {
  Serial.begin(9600);


  pinMode(bluePin, OUTPUT);         // Enables digital output though pin
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);


}

void loop() {
      double res = volateToResistance(ThermistorPin), temperature = temp(res);
      Serial.print("Temperature: ");
      Serial.print(temperature,1);
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
double temp(double x)
{
  double A = -1.977896389*pow(10,-5);
  double B = 5.037638471*pow(10,-4);
  double C = -3.981748374*pow(10,-3);
  double D = 1.277712116*pow(10,-2);

  x = log(x);
  
  T = 1/(A*pow(x,3) + B*pow(x,2) + C*x + D);
  
  return T-273.15;
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
  if(blue1 <= temp && blue2 >= temp)
    digitalWrite(bluePin, HIGH);
  else
    digitalWrite(bluePin, LOW);

  if(green1 < temp && green2 > temp)
    digitalWrite(greenPin, HIGH);
  else
    digitalWrite(greenPin, LOW);
  
  if(red1 <= temp && red2 > temp)
    digitalWrite(redPin, HIGH);  
  else
    digitalWrite(redPin, LOW);
}
