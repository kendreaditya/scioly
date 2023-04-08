#include <Arduino.h>
#include <TM1637Display.h>

#include <Wire.h>
#include <LPS.h>

// Module connection pins (Digital Pins)
#define CLK 8
#define DIO 9

LPS ps;

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   500

TM1637Display display(CLK, DIO);

void setup()
{
  display.clear();
  Serial.begin(9600);
  Wire.begin();

  if (!ps.init())
  {
    Serial.println("Failed to autodetect pressure sensor!");
    while (1);
  }

  ps.enableDefault();
}

void loop()
{
  display.setBrightness(0x0f);
  float pressure = ps.readPressureMillibars();
  float altitude = ps.pressureToAltitudeMeters(pressure);
  float temperature = ps.readTemperatureC();
  float h = ((pow(1012/pressure,1/5.257)-1)*(temperature+273.15))/0.0065;
 
}
 
    
