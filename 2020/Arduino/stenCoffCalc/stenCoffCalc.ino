int ThermistorPin = 0;
double logR2, R2, T, total;
double A, B, C;  // Steinhart-Hart and Hart Coefficients
double Temp[3] = {41.27+273.15, 3.8+273.15, 64.7+273.15}, R[3] = {5665.8, 26374.2, 2573.0};

int R_fixed = 5973, n = 3, delayTime = 200, i = 3;

void setup() {
  Serial.begin(9600);
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
  for (int i = 0; i < 10; i++) total += analogRead(pin);
  double R_thermistor = R_fixed * total / (10230 - total);
  return R_thermistor;
}
