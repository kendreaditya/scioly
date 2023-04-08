// The Ardunio voltage fluxuates too much
// NEED more constant source of voltage

#include <Wire.h>
#include <TM1637Display.h>
#include <string.h>
#define CLK 6
#define DIO 5
int Resistor = 2000;                      // Resistor Ohm
bool clab = false;
int ThermistorPin = 0;
const int bluePin = 4, greenPin = 2, redPin = 3;
float a = -0.03067864648568446, b = 0.0060572796303777505, c = -0.00002775603807601169;

TM1637Display display(CLK, DIO);

void setup() {
Serial.begin(9600);
display.setBrightness(0x0f);
pinMode(bluePin, OUTPUT);
pinMode(redPin, OUTPUT);
pinMode(greenPin, OUTPUT);

}

void loop() {

  float T[3], R[3];

  while (Serial.available() == 0){
    String  tempin = (String)Serial.read();
    T[0] = (float)tempin.substring(0, 2);
    T[1] = (float)tempin.substring(4, 6);
    T[2] = (float)tempin.substring(7, 9);
  }
  
  //Serial.print(T[0]);
  
  /*
  while (Serial.available() == 0){};
  T[1] = Serial.read();
  Serial.print(T[1]);
  

  while (Serial.available() == 0){}
  T[2] = Serial.read();
  Serial.print(T[2]);
  
  */

  for(int x = 0; x < 3; x++)
  {
    
    R[x] = 3;

    // Serial.print("What is the temperature right now? (C)");
      
  }

  float l1 = log(R[0]), l2 = log(R[1]), l3 = log(R[2]);
  float y1 = 1/T[0], y2 = 1/T[1], y3 = 1/T[2];
  float g2 = (y2-y1)/(l2-l1), g3 = (y3-y1)/(l3-l1);

  c = ((g3-g2)/(l3-l2))*pow(l1+l2+l3, -1);
  b = g2 - c*(l1*l1 + l1*l2 + l2*l2);
  a = y1 - ((b + l1*l1*c)*l1);

  clab = true;
  
  // steinhartHart();

  Serial.print("Steinhart done");

  if (clab == true) 
  {  
  float R = analogRead(ThermistorPin), T;   // ADC Value
    
  //Serial.print("Resistance (Ohm): "); 
  //Serial.println(R * 4.9,2);
  
  //Serial.print("Voltage (Defult): ");
  //Serial.println(analogRead(1) *0.0049,2 );

  display.showNumberDec(R * 0.49);

  R = Resistor / (1023.0 / (float)R - 1.0);
  T = 1.0 / (a + b*log(R) + c*log(R)*log(R)*log(R));
  T = T - 273.15;
  
  Serial.print("LED Color: ");
  Serial.println(led(T));
  Serial.print("Temperature (Probe): "); 
  Serial.print(T,5);
  Serial.println(" C");

  display.showNumberDec(T*100,0);

  Serial.println();
  delay(2000);
  }
}

void steinhartHart()
{
  float T[3], R[3];

  while (Serial.available() > 0){
    T[0] = Serial.read();
    Serial.print(T[0]);
  }

  while (Serial.available() > 0){
    T[1] = Serial.read();
    Serial.print(T[1]);
  }

  while (Serial.available() > 0){
    T[2] = Serial.read();
    Serial.print(T[2]);
  }
  

  for(int x = 0; x < 3; x++)
  {
    
    R[x] = 3;

    // Serial.print("What is the temperature right now? (C)");
      
  }

  float l1 = log(R[0]), l2 = log(R[1]), l3 = log(R[2]);
  float y1 = 1/T[0], y2 = 1/T[1], y3 = 1/T[2];
  float g2 = (y2-y1)/(l2-l1), g3 = (y3-y1)/(l3-l1);

  c = ((g3-g2)/(l3-l2))*pow(l1+l2+l3, -1);
  b = g2 - c*(l1*l1 + l1*l2 + l2*l2);
  a = y1 - ((b + l1*l1*c)*l1);

  clab = true;
}


String led(float temp)
{
  int blue1 = 0, blue2 = 25;      // Blue LED Ranges
  int green1 = 26, green2 = 50;   // Green LED Ranges
  int red1 = 51, red2 = 90;       // Red LED  Ranges
  
  String color = "null";

  if(blue1 < temp && blue2 > temp)
  {
    digitalWrite(bluePin, HIGH);
    color = "blue";
    delay(1000);  
  }
  else if(green1 < temp && green2 > temp)
  {
    digitalWrite(greenPin, HIGH);
    color = "green";
    delay(1000);  
  }
  else if(red1 < temp && red2 > temp)
  {
    digitalWrite(redPin, HIGH);  
    color = "red";
    delay(100);  
  }
  return color;
}
