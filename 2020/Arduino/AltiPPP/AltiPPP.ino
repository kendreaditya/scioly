#include <Arduino.h>
#include <TM1637Display.h>

#include <Wire.h>
#include <LPS.h>

LPS ps;

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   2000

TM1637Display display(CLK, DIO);
const int STcp = 10;      //Pin connected to ST_CP of 74HC595
const int SHcp = 9;       //Pin connected to SH_CP of 74HC595 
const int DS = 8;         //Pin connected to DS of 74HC595

const int CLK = 9;       //Pin connected to SH_CP of 74HC595 
const int DIO = 8;         //Pin connected to DS of 74HC595 

void setup()
{
  Wire.begin();
  pinMode(STcp,OUTPUT);
  pinMode(SHcp,OUTPUT);
  pinMode(DS,OUTPUT);
  
  
  
  ps.enableDefault();
}

void loop()
{
  digitalWrite(STcp,LOW); // IDK what this does... ground ST_CP and hold low for as long as you are transmitting
  display.setBrightness(0x0f);
  float pressure = ps.readPressureMillibars();
  float temperature = ps.readTemperatureC();
  float h = ((pow(1012/pressure,1/5.257)-1)*(temperature+273.15))/0.0065;

  display.showNumberDec(h);
}
