struct Constants
{
  const double K = 273.15;
  const double Vout = 3.3;
};

struct TempRange
{
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

struct Pins
{
  const static int THERMISTOR = 0;
  const static int RED = 10;
  const static int GREEN = 11;
  const static int BLUE = 12;
};
struct TempEqCoefficients {
  static double A = 0.00072505860328674;
  static double B = 0.00028580390930175;
  static double C = -0.00000002258041620;

  static double newA;
  static double newB;
  static double newC;
};



void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
