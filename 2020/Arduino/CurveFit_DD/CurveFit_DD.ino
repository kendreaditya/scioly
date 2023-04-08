/*
* input -2 for temp for that instance of resistance
* dataPoints = the amount of data points that will be collected
* 
* To D0:
*   account for fulxuations in voltage with equation (R = (volt/((analogRead(analogPin)*volt)/1024.0)) - 1)
*   anytime you say -2 it should give prdectiojn all other times not
*   able to exclude data points
*   16 bit adc
*   more accurea volatage
*   take rage of volate for like 1 sec
*/

#include <Wire.h>

double denom, x, y, a, b, c;


int const dataPoints = 10;
int ThermistorPin = 0, i = 0, order = 3;
double resistance = 2000.0, temps[dataPoints], resist[dataPoints], coeffs[3];

void setup() {
  Serial.begin(9600);
}
void loop() {
  while(Serial.available() > 0 and i < dataPoints) {
    temps[i] = Serial.readString().toFloat();
    resist[i] = volateToResistance();
    Serial.println("Temp (x): "+ (String)temps[i]+ " Resistance(y): "+ (String)resist[i]);
    i++;
  }  

    if(i >= dataPoints and Serial.readString().toInt() == -2)
  {
    //int ret = fitCurve(order, dataPoints, temps, resist, sizeof(coeffs)/sizeof(resist), coeffs); // order, amount of points, x, y, sizeof(coeffs)/sizeof(double), coeffs);
    Serial.println((String)volateToResistance());
    PolynomialFit(dataPoints, temps, resist, order);
    for (i=0;i<order;i++)
    {
        Serial.print(" + ("+(String)coeffs[i]+")"+"x^"+ (String)i);
    }
    
    Serial.println("\n"+(String)calculateX(volateToResistance(), coeffs[0], coeffs[1], coeffs[2]));
    }
  
  
}

double calculateX(double y, double c, double b, double a)
{
  return (-b+sqrt((b*b)-(4*a*c)))/(2*a)+y;
}

double volateToResistance()
{
  return ((1024.0/analogRead(ThermistorPin))-1)*resistance;
}

void PolynomialFit(int N, double x[], double y[],int n){
    int i,j,k; // N = amount of numbers, n is the degree of Polynomial 
    double X[2*n+1];                        //Array that will store the values of sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
    for (i=0;i<2*n+1;i++)
    {
        X[i]=0;
        for (j=0;j<N;j++)
            X[i]=X[i]+pow(x[j],i);        //consecutive positions of the array will store N,sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
    }
    double B[n+1][n+2],a[n+1];            //B is the Normal matrix(augmented) that will store the equations, 'a' is for value of the final coefficients
    for (i=0;i<=n;i++)
        for (j=0;j<=n;j++)
            B[i][j]=X[i+j];            //Build the Normal matrix by storing the corresponding coefficients at the right positions except the last column of the matrix
    double Y[n+1];                    //Array to store the values of sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
    for (i=0;i<n+1;i++)
    {    
        Y[i]=0;
        for (j=0;j<N;j++)
        Y[i]=Y[i]+pow(x[j],i)*y[j];        //consecutive positions will store sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
    }
    for (i=0;i<=n;i++)
        B[i][n+1]=Y[i];                //load the values of Y as the last column of B(Normal Matrix but augmented)
    n=n+1;                //n is made n+1 because the Gaussian Elimination part below was for n equations, but here n is the degree of polynomial and for n degree we get n+1 equations
    for (i=0;i<n;i++)                    //From now Gaussian Elimination starts(can be ignored) to solve the set of linear equations (Pivotisation)
        for (k=i+1;k<n;k++)
            if (B[i][i]<B[k][i])
                for (j=0;j<=n;j++)
                {
                    double temp=B[i][j];
                    B[i][j]=B[k][j];
                    B[k][j]=temp;
                }
    
    for (i=0;i<n-1;i++)            //loop to perform the gauss elimination
        for (k=i+1;k<n;k++)
            {
                double t=B[k][i]/B[i][i];
                for (j=0;j<=n;j++)
                    B[k][j]=B[k][j]-t*B[i][j];    //make the elements below the pivot elements equal to zero or elimnate the variables
            }
    for (i=n-1;i>=0;i--)                //back-substitution
    {                        //x is an array whose values correspond to the values of x,y,z..
        a[i]=B[i][n];                //make the variable to be calculated equal to the rhs of the last equation
        for (j=0;j<n;j++)
            if (j!=i)            //then subtract all the lhs values except the coefficient of the variable whose value                                   is being calculated
                a[i]=a[i]-B[i][j]*a[j];
        a[i]=a[i]/B[i][i];            //now finally divide the rhs by the coefficient of the variable to be calculated
    }
    for (i=0;i<n;i++)
        coeffs[i] = a[i];
}
