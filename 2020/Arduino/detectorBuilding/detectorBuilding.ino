const double TEMP_ADJUST = 0.0;

const double KELVIN_CONVERSION = 273.15;
const double Vin = 5;
const int ADC_BIT = pow(2, 10) - 1;
const long FIXED_RESISTOR = 5973;

struct TempRange {
  const static double RED_RANGE[2] = {0, 20};
  const static double GREEN_RANGE[2] = {20, 40};
  const static double BLUE_RANGE[2] = {40, 60};

  const static bool RED_EQUAL_TO[2] = {true, true};
  const static bool GREEN_EQUAL_TO[2] = {true, true};
  const static bool BLUE_EQUAL_TO[2] = {true, true};

  static bool inRange(double TEMP, double RANGE[], bool EQUAL_TO[])
  {
    if(EQUAL_TO[0] == true && EQUAL_TO[1] == true)
      return (TEMP >= RANGE[0] && RANGE[1] >= TEMP) ? true : false;
    else if(EQUAL_TO[0] == true && EQUAL_TO[1] == false)
      return (TEMP >= RANGE[0] && RANGE[1] > TEMP) ? true : false;
    else if(EQUAL_TO[0] == false && EQUAL_TO[1] == true)
      return (TEMP > RANGE[0] && RANGE[1] >= TEMP) ? true : false;
    else if(EQUAL_TO[0] == false && EQUAL_TO[1] == false)
      return (TEMP > RANGE[0] && RANGE[1] > TEMP) ? true : false;

    return false;
  }
};

struct Pins {
  const static int THERMISTOR = 0;
  const static int RED = 10;
  const static int GREEN = 11;
  const static int BLUE = 12;
};

//Coefficients for Steinhart-Hart equation
struct TempEqCoeffs {
  constexpr static double A = 0.00072505860328674;
  constexpr static double B = 0.00028580390930175;
  constexpr static double C = -0.00000002258041620;
};

//Serial monitor commands
struct Commands {
  const static String EXAMPLE;
};

const String Commands::EXAMPLE = "EXAMPLE";

class dataCalculator {
  private:
    const static int NUM_RES = pow(2,10);
    static double thermVolt;
    static double thermRes;
    
  public:
    static double getAvgRes()
    {
      double adcSum = 0;
      for (int i = 0; i < NUM_RES; i++) {
        adcSum += analogRead(Pins::THERMISTOR);
      }
      thermVolt = calcVoltage(adcSum / NUM_RES);
      thermRes = voltageDivider(thermVolt);
      return thermRes;
    }

    static double voltageDivider(double Vout) {
      return FIXED_RESISTOR * ((Vin/Vout) - 1);
    }
    
    static double calcVoltage(int adcValue) {
      return Vin*(adcValue/ADC_BIT);
    }

    static double calcTemp(double res) {
      double lnRes = log(res);
      double temp = pow(TempEqCoeffs::A + (TempEqCoeffs::B*pow(lnRes, 2)) + (TempEqCoeffs::C*pow(lnRes, 3)), -1);
      return temp - KELVIN_CONVERSION - TEMP_ADJUST;
    }

    static double getThermVolt() {return thermVolt;}
    static double getThermRes() {return thermRes;}
};

}

void setup() {
  Serial.begin(9600);

  pinMode(Pins::RED, OUTPUT);
  pinMode(Pins::GREEN, OUTPUT);
  pinMode(Pins::BLUE, OUTPUT);
}

void loop() {
  //0 to 1023
  int analogValue = analogRead(Pins::THERMISTOR);

  //Voltage drop across fixed resistor
  double voltageDrop_fixed = analogValue * (V_OUT / 1023.0);

  //Voltage drop across thermistor
  double voltageDrop_therm = V_OUT - voltageDrop_fixed;

  //Thermistor resistance (value used for debugging)
  double thermResistance = FIXED_RESISTOR * (V_OUT / voltageDrop_fixed - 1.0);

  //Temperature reading using vltage drop across thermistor
  double thermTemperature = getTemperature(voltageDrop_therm);

  //Check/read commands entered through serial monitor
  Calibrator::checkCalibrate(thermResistance);

  TempAccumulator::addTemp(thermTemperature);
  
  if (ReadingDisplay::show) {
    if (ReadingDisplay::debug) {
      Serial.println(
        "Analog Value: " + String(analogValue) + 
        " | Resistor V Drop (volts): " + String(voltageDrop_fixed, 8) + 
        " | Thermistor V Drop (volts): " + String(voltageDrop_therm, 8) + 
        " | Thermistor R (ohms): " + String(thermResistance, 8) + 
        " | Temp.(deg. C): " + (TempAccumulator::canDisplayTemp ? String(TempAccumulator::getAvgTemp(), 8) : "NOT ENOUGH DATA")
      );
    }
    else {
      Serial.println(
        "Resistor V Drop (volts): " + String(voltageDrop_fixed, 8) + 
        " | Thermistor V Drop (volts): " + String(voltageDrop_therm, 8) + 
        " | Temp.(deg. C): " + (TempAccumulator::canDisplayTemp ? String(TempAccumulator::getAvgTemp(), 8) : "NOT ENOUGH DATA")
      );
    }
  }

  else
    if(TempRange::inRange(thermTemperature, TempRange::BLUE_RANGE, TempRange::BLUE_EQUAL_TO))
      digitalWrite(Pins::BLUE, HIGH);
    else
      digitalWrite(Pins::BLUE, LOW);
    
    if(TempRange::inRange(thermTemperature, TempRange::GREEN_RANGE, TempRange::GREEN_EQUAL_TO))
      digitalWrite(Pins::GREEN, HIGH);
    else
      digitalWrite(Pins::GREEN, LOW);

    if(TempRange::inRange(thermTemperature, TempRange::RED_RANGE, TempRange::RED_EQUAL_TO))
      digitalWrite(Pins::RED, HIGH);
    else
      digitalWrite(Pins::RED, LOW);
  }
  
  delay(50);
}
