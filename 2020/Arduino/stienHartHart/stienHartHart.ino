#include <Wire.h>
int ThermistorPin = 0;
double logR2, R2, T, total;
double A, B, C;  // Steinhart-Hart and Hart Coefficients
double Temp[3], R[3];

int R_fixed = 5973, n = 3, delayTime = 200, i = 0;
int bluePin = 7, greenPin = 5, redPin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  //analogReference(EXTERNAL);
}
void loop() {
    while (Serial.available() > 0 and n > i)
    {
      Temp[i] = Serial.readString().toFloat()+273.15;
      R[i] = volateToResistance(ThermistorPin);
      Serial.println("--------------------------");
      Serial.println(Temp[i],2);
      Serial.println(R[i],2);
      Serial.println("--------------------------");
      i++;
    }
    if(n > i)
    {
      Serial.print("Thermistor resistance: ");
      Serial.println(volateToResistance(ThermistorPin));
      delay(1000);
    }
   
    if(n == i)
    {
      double l1 = log(R[0]), l2 = log(R[1]), l3 = log(R[2]);
      double y1 = 1/Temp[0], y2 = 1/Temp[1], y3 = 1/Temp[2];
      double g2 = (y2-y1)/(l2-l1), g3 = (y3-y1)/(l3-l1);

      C = ((g3-g2)/(l3-l2))*pow(l1+l2+l3, -1);
      B = g2 - C*(l1*l1 + l1*l2 + l2*l2);
      A = y1 - ((B + l1*l1*C)*l1);

      Serial.print("A: ");
      Serial.println(A, 17);
      Serial.print("B: ");
      Serial.println(B, 17);
      Serial.print("C: ");
      Serial.println(C, 17);
      i++;
    }
   
   if (Serial.available() > 0 and n < i)
    { 
      double res = volateToResistance(ThermistorPin);
      Serial.println("--------------------------");
      Serial.print("TEMP RIGHT NOW = ");
      Serial.print(temp(res, A, B, C),3);
      Serial.println(" C");
      Serial.print("Resistance = ");
      Serial.print(res);
      Serial.println(" ohms");
       Serial.print("Voltage = ");
      Serial.print(1023/analogRead(ThermistorPin), 2);
       Serial.println(" volts");
      Serial.println("--------------------------");
      
      delay(2000);
    }
   if(n < i)
   {
    double res = volateToResistance(ThermistorPin);
    double currentTemp = temp(res, A, B, C);
    Serial.print("TEMP = ");
    Serial.print(currentTemp,3);
    Serial.println(" C");

    led(currentTemp);
    delay(1000);      
   }
}
double temp(double R2, double A_, double B_, double C_)
{
  logR2 = log(R2);
  T = (1.0 / (A_ + B_*logR2 + C_*logR2*logR2*logR2));  // Steinhart and Hart Equation. T  = 1 / {A + B[ln(R)] + C[ln(R)]^3}
  return T - 273.15;
}
double volateToResistance(int pin)
{
  total = 0; // reset
  for (int i = 0; i < 10; i++) total += analogRead(pin); // 10 readings
  double R_thermistor = R_fixed * total / (10230 - total);
  return R_thermistor;
}
void led(double temp)
{
  int blue1 = 50, blue2 = 70;      // Blue LED Ranges
  int green1 = 0, green2 = 40;   // Green LED Ranges
  int red1 = 40, red2 = 50;       // Red LED  Ranges
  
  if(blue1 < temp && blue2 > temp)
  {
    digitalWrite(bluePin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, LOW);
  }
  else if(green1 < temp && green2 > temp)
  {
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
    digitalWrite(redPin, LOW);
  }
  else if(red1 < temp && red2 > temp)
  {
    digitalWrite(redPin, HIGH);  
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
  }
}
