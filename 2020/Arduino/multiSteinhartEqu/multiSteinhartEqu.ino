/*
* input -2 for temp for that instance of resistance
* dataPoints = the amount of data points that will be collected
* 
* To D0:
*   x account for fulxuations in voltage with equation (R = (volt/((analogRead(analogPin)*volt)/1024.0)) - 1)
*   x anytime you say -2 it should give prdectiojn all other times not
*   x more accurea volatage
*   x take rage of volate for like 1 sec
*   x display cofficents
*   x LED Fucntion
*   
*   able to exclude data points
*   16 bit adc
*   Display that shows temp
*   reset porgam without uploading
*   temp change quick (no shurink tubeing)
*   stand to hold thermistor in place with other temp reader
*   get insulated thermistor
*   
*   what if used ntc for low and ptc for high?
*   can we bring contarin to keep water insulate at that tempuratre?
*   contact vernier on their process of clalbrating
*/

#include <Wire.h>
#include <Arduino.h>
int ThermistorPin = 0, reffPin = 1, bluePin = 11, greenPin = 12, redPin = 13;
int Vo, i = 0;
float logR2, R2, T;
float A, B, C;  // Steinhart-Hart and Hart Coefficients
float Temp[3], R[3];

int n = 3, resistance = 10000, delayTime = 200;


void setup() {
  Serial.begin(9600);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
}

void loop() {
    while (Serial.available() > 0 and n > i)
    {
      Temp[i] = Serial.readString().toFloat()+273.15;
      float avg = 0;
      for(int x = 0; x < 10; x++)
      {
        avg += volateToResistance();
        delay(delayTime);
      }

      R[i] = avg/10.0;
      Serial.println(Temp[i]);
      Serial.println(R[i]);
      i++;
    }
    
    if(n == i)
    {
      float l1 = log(R[0]), l2 = log(R[1]), l3 = log(R[2]);
      float y1 = 1/Temp[0], y2 = 1/Temp[1], y3 = 1/Temp[2];
      float g2 = (y2-y1)/(l2-l1), g3 = (y3-y1)/(l3-l1);

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
   
   if (Serial.available() > 0 and n < i and Serial.readString().toFloat() == -2.0)
    {
      float avg = 0;
      for(int x = 0; x < 10; x++)
      {
        avg += volateToResistance();
        delay(delayTime);
      }
      R2 = avg/10;
      
      logR2 = log(R2);
      T = (1.0 / (A + B*logR2 + C*logR2*logR2*logR2));  // Steinhart and Hart Equation. T  = 1 / {A + B[ln(R)] + C[ln(R)]^3}
      T =  T - 273.15;
      Serial.print("TEMP = ");
      Serial.print(T,3);
      Serial.println(" C");
      Serial.println(R2);
      
    }
    if(n < i)
    {
      R2 = volateToResistance();
      logR2 = log(R2);
      T = (1.0 / (A + B*logR2 + C*logR2*logR2*logR2));  // Steinhart and Hart Equation. T  = 1 / {A + B[ln(R)] + C[ln(R)]^3}
      T =  T - 273.15;
      led(T);
      delay(delayTime);
    }
}

float volateToResistance()
{
  float voltage = analogRead(reffPin) * 5.0/1023.0;
  float Vout= (analogRead(ThermistorPin) * voltage)/1023.0;
  return resistance * (voltage/Vout) -1;
}

void led(float temp)
{
  int blue1 = 0, blue2 = 25;      // Blue LED Ranges
  int green1 = 26, green2 = 50;   // Green LED Ranges
  int red1 = 51, red2 = 90;       // Red LED  Ranges
  
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
