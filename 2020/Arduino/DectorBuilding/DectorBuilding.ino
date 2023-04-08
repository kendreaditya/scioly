/*
* input -2 for temp for that instance of resistance
* dataPoints = the amount of data points that will be collected
* 
* To D0:
*   implment LinearRegression class locally
*   account for fulxuations in voltage with equation (R = (volt/((analogRead(analogPin)*volt)/1024.0)) - 1)
*/

#include <Wire.h>
#include <LinearRegression.h>
LinearRegression lr = LinearRegression(0,75);

int const dataPoints = 6;

float resistance = 2000.0, temps[dataPoints], resist[dataPoints];
int ThermistorPin = 0, i = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  while(Serial.available() > 0 and i < dataPoints) {
    temps[i] = Serial.readString().toFloat();
    resist[i] = volateToResistance(analogRead(ThermistorPin));
    lr.learn(temps[i], resist[i]);
    Serial.println("Temp (x): "+ (String)temps[i]+ " Resistance(y): "+ (String)resist[i]);
    i++;
  }

    if(i >= dataPoints and Serial.readString().toInt() == -2)
  {
    Serial.println((String)lr.calculateX(volateToResistance(analogRead(ThermistorPin))));
  }
}

float volateToResistance(float volt)
{
  return ((1024.0/volt)-1)*resistance;
}
