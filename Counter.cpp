/*
Counter calculation
*/

#include "Arduino.h"
#include "Counter.h"

int amm = 0;

void Counter::increment(int ammount){
  amm = amm+ammount;
}

void Counter::decremet(int ammount){
  amm = amm-ammount;
}

void Counter::reset(){
  amm = 0;
}

int Counter::getAmmount(){
  return amm;  
}
