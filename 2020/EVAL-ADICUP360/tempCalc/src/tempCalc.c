/*****************************************************************************
 * File Name: tempCalc.c
 * Creator: Aditya Kendre
 * Discription:
 * Uses Steinhart coefficients to calculate temperature based on resistance
 *****************************************************************************/

#include <sys/platform.h>
#include "tempCalc.h"

/* DO NOT CHANGE THIS */
const double R_FIXED = 10000;
const int BLUE_PIN = 0, GREEN_PIN = 1, RED_PIN = 2, THERM_PIN = 0;

/* Temperature Ranges*/
double BLUE[] = {0.0, 25.0};
double GREEN[] = {25.1, 50.0};
double RED[] = {50.1, 75.0};

/* Coefficients */
const double A = 0.00091717205047607;
const double B = 0.00023593959808349;
const double C =  0.00000013877954483;


int main(int argc, char *argv[])
{

	double therm_res = volateToResistance(THERM_PIN), temperature = temp_calc(therm_res);
	
	 AdcGo(pADI_ADC1,ADCMDE_ADCMD_IDLE);			// Places the ADC1 in Idle mode
	 AdcMski(pADI_ADC1,ADCMSKI_RDY,1);              // Enable ADC ready interrupt source
	 /*
	Serial.print("Temperature: ");
	Serial.print(temperature,1);
	Serial.println(" C");

	Serial.print("Resistance: ");
	Serial.print(therm_res, 1);
	Serial.println(" ohm");

	Serial.print("Voltage:");
	Serial.print((analogRead(THERM_PIN) * 5.015) / 1024.0, 4);
	Serial.println(" volts");
*/
	led(temperature);
	delay(1000);

	return 0;
}

double temp_calc(double R2)
{
  return (1.0 / (A + B*log(R2) + C*log(R2)*log(R2)*log(R2))) - 273.15;
}
double volateToResistance(int PIN)
{
  int total = 0; // reset
  for (int i = 0; i < 10; i++) total += analogRead(PIN); // Change analogRead function
  return R_FIXED * total / (10230 - total); // change 10 bit num
}
void led(double temp)
{
  if(BLUE[0] < temp && BLUE[1] > temp) // Adjust all the digitalWire function, and High/Low
    digitalWrite(BLUE_PIN, HIGH);
  else
    digitalWrite(BLUE_PIN, LOW);

  if(GREEN[0] < temp && GREEN[1] > temp)
    digitalWrite(GREEN_PIN, HIGH);
  else
    digitalWrite(GREEN_PIN, LOW);

  if(RED[0] < temp && RED[1] > temp)
    digitalWrite(RED_PIN, HIGH);
  else
    digitalWrite(RED_PIN, LOW);
}

void ADC_CALIBRATION()
{
	AdcGo(pADI_ADC1,ADCMDE_ADCMD_IDLE); //Set ADC channel in idle mode
	timer_sleep(1);

	AdcGo(pADI_ADC1,ADCMDE_ADCMD_INTOCAL); // ADC1 internal Zero scale calibration
	while ((AdcSta(pADI_ADC1) &0x20) != 0x20);       // bit 5 set by adc when calibration is complete

	AdcGo(pADI_ADC1,ADCMDE_ADCMD_IDLE); //Set ADC channel in idle mode
	timer_sleep(1);
}


