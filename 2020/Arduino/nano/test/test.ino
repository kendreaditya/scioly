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
    int ThermistorPin = 0, reffPin = 1;
    int resistance = 10000;


    void setup() {
      Serial.begin(9600);

    }

    void loop() {
      float avg = 0;
  
          for(int x = 0; x < 10; x++)
          {
            avg += volateToResistance();
            delay(50);
    
          }
          Serial.println(avg/10.0);
        delay(5);
    }
    float volateToResistance()
    {
      float voltage = analogRead(reffPin) * 5.0/1023;
      float Vout= (analogRead(ThermistorPin) * voltage)/1024.0;
      return resistance * (voltage/Vout) -1;
    }
