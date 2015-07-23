/*
Temperature calculation
*/

#include "Arduino.h"
#include "Temperature.h"

double Temperature::thermister(int RawADC) {
 double Temp;
 Temp = log(((1024000/RawADC) - 1000));
// Assuming a 1k Thermistor.  
//Calculation is actually: Resistance = (1024 * BalanceResistor/ADC) - BalanceResistor

 Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
 Temp = Temp - 273.15; // Convert Kelvin to Celcius
 return Temp;
}
