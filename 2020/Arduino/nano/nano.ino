int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
#include <Adafruit_ADS1015.h>

  const float multiplier = 1; 

Adafruit_ADS1115 ads;
void setup() {
Serial.begin(9600);
 ads.setGain(GAIN_TWOTHIRDS);
ads.begin();
}

void loop() {

  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
 
  float adc0, adc1, adc2, adc3;
  adc1 = ads.readADC_SingleEnded(1)*multiplier;
  adc3 = ads.readADC_SingleEnded(3)*multiplier;
  
  Serial.println(10000*((adc3/adc1)-1));
  //Serial.println(adc3);
  delay(0);
}
