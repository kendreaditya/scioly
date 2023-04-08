#include <avr/sleep.h>

int normADC[10]; //Create an arrray to hold the "normal" or non-low noise ADC measurements
int lowNoiseADC[10]; //Create an array to hold the low noise ADC measurements

int const aVCC = 0b01000000; //variable to set ADC to use VCC as reference
int const iREF = 0b11000000; //variable to set ADC to use internal 1.1V as reference
int const aREF = 0b00000000; //variable to set ADC to use VCC as reference
//bits 7 and 6 select the ADC reference source
//The four zeros (bits 3 thru 0) at the end of the above binary register values sets the analog channel to A0
//Bit 5 selects right adjust for the result and bit 4 is not used

int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {
ADMUX = aVCC; //Configure the ADC via the ADMUX register for VCC as reference, result right adjust, and source A0 pin
  ADCSRA |= 1<<ADEN; //Turn the ADC on by setting the ADEN bit to 1 in the ADCSRA register
  ADCSRA |= 1<<ADIE; //Setting the ADIE bit to 1 means when the ADC is done a measurement it generates an interrupt, the interrupt will wake the chip up from low noise sleep
  ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));    //Prescaler at 128 so we have an 125Khz clock source
  //The ADC clock must be between 50kHz and 200kHz, since the Uno clock is 16MHz we want to divide it by 128 to get 125kHz. This may need to be adjusted for other Arduino boards
  //We do not have to use registers to set the sleep mode since we are using the avr/sleep.h library
  sleep_enable(); //enable the sleep capabili and send it over serial with three decimal places precision
  
}

void loop() {
  set_sleep_mode(SLEEP_MODE_ADC); //set the type of sleep mode. We are using the ADC noise reduction sleep mode
  //Note that in this sleep mode the chip automatically starts an ADC measurement once the chip enters sleep mode
  //Note that the reason for making the ADC measurements and storing in arrays was to avoid using the arduino serial functions with sleep mode since serial uses interrupts
   //Loop ten times and make ten ADC measurements in low noise mode
    sei(); //enable interrupts
    sleep_cpu(); //enter low ADC noise sleep mode, this action turns off certain clocks and other modules in the chip so they do not generate noise that affects the accuracy of the ADC measurement
    //The chip remains in sleep mode until the ADC measurement is complete and executes an interrupt which wakes the chip from sleep
    Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0; 
  Serial.begin(9600); //Start serial comm to print out results to serial monitor
  Serial.println("Noise reduction:"); //labels the readings being printed
    Serial.println(T); //Convert each low noise measurement to a voltage level

    while(1);
}
