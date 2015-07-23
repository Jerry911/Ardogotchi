/*
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# authors: Jeroen Pleysier - Jorrit Bloemen (jeroen.pleysier@gmail.com)
# date: 2014-10-10
# version 1.7
# description: this program loads and displays a bitmap onto
#              an arduino compatible TFT LCD screen
#	       v1.7 includes lifestages for the tamagotchi
#	       and supports a temperature sensor to mimick
#              good conditions to hatch faster, number of
#              lifes, feeding and dying.
#              Also included is a push button to feed the
#              tamagotchi to prevent it from dying.
#              it is writen in C (arduino)
*/

// include the necessary libraries
#include <SPI.h>
#include <SD.h>
#include <TFT.h>
#include <math.h>
#include "Temperature.h"
#include "Counter.h"

// pin definitions
#define sd_cs  4
#define lcd_cs 10
#define dc     9
#define rst    8

int hatch = 0;
int lifestage = 0;
int HUNGRY_INCREMENT = 10;
TFT TFTscreen = TFT(lcd_cs, dc, rst);
File values;
Temperature temperature;
PImage bitmap;
PImage heart;
PImage stagetwo;
PImage tocold;
PImage dead;
PImage tohot;
PImage egg;
Counter c;
Counter hungry;

void setup() {
  //5v for NTC
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);

  //5V for button
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);

  //Interrupt for button
  //0 = pin2
  //isr = method to do
  //when CHANGE,RISING,LOW,FALLING
  attachInterrupt(0, isr, CHANGE);

  initTFT();
  initSD();
  //load bitmaps
  heart = TFTscreen.loadImage("heart.bmp");
  egg = TFTscreen.loadImage("eggone.bmp");
  stagetwo = TFTscreen.loadImage("stagetwo.bmp");
  tocold = TFTscreen.loadImage("tocold.bmp");
  tohot = TFTscreen.loadImage("tohot.bmp");
  dead = TFTscreen.loadImage("dead.bmp");
  initFiles();
}

void isr() {
  byte a = digitalRead(2);
  //lower ammount of hungryness when pushed
  if(a == 1){
    hungry.decremet(5);
  }
}


void loop() {
  double temp = double(temperature.thermister(analogRead(0)));
  hungry.increment(HUNGRY_INCREMENT);

  if (temp > 18) {
    c.increment(10);
  } else {
    c.increment(5);
  }

  if (lifestage == 0) {
    drawEgg();
    lifestage++;
  }

  if (c.getAmmount() == 10000 && lifestage == 1) {
    doHatch();
  }

  if (lifestage >= 2) {
    drawTamagotchi();
    drawLives();
  }

  delay(2000);
}

void drawLives() {
  //white edge rect
  TFTscreen.stroke(255, 255, 255);
  //white inside rect
  TFTscreen.fill(255, 255, 255);
  //draw rect
  TFTscreen.rect(0, 0, 160, 20);

  int ammo = hungry.getAmmount();
  Serial.println(ammo);
  //screen is 160px wide and icon is 16wide
  if (ammo <= 1000) {
    TFTscreen.image(heart, 144, 0);
    TFTscreen.image(heart, 127, 0);
    TFTscreen.image(heart, 110, 0);
  }

  if (ammo >= 1000 && ammo < 2000) {
    TFTscreen.image(heart, 144, 0);
    TFTscreen.image(heart, 127, 0);
  }

  if (ammo >= 2000 && ammo <= 3000) {
    TFTscreen.image(heart, 144, 0);
  }

  if (ammo > 3000) {
    // draw the image
    TFTscreen.image(dead, 15, 25);
    // quit
    exit(0);
  }
}

void drawEgg() {
  // set the fill color to white
  TFTscreen.fill(255, 255, 255);
  // set the stroke color to white (edge of rect)
  TFTscreen.stroke(255, 255, 255);
  //clear the area where the egg is
  //(xStart, yStart, width, height)
  TFTscreen.rect(45, 25, 70, 80);
  // draw the image
  TFTscreen.image(egg, 45, 25);
}

void doHatch() {
  lifestage = 2;
  writeLifestage();
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.rect(0, 0, 130, 15);
}

void drawTamagotchi() {
  double temp = double(temperature.thermister(analogRead(0)));

  if (temp > 22) {
    TFTscreen.image(tohot, 15, 25);
  }

  if (temp < 8) {
    TFTscreen.image(tocold, 15, 25);
  }

  if (temp <= 22 && temp >= 8) {
    TFTscreen.image(stagetwo, 15, 25);
  }
}

void initTFT() {
  // initialize the GLCD and show a message
  TFTscreen.begin();
  TFTscreen.background(255, 255, 255);
  //blue
  TFTscreen.stroke(0, 0, 255);
  TFTscreen.println();
  TFTscreen.println("Tamagotchi v1.7");
  //black
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.println("Open serial monitor");
  TFTscreen.println("to run the sketch");
  delay(2000);

  // initialize the serial port: it will be used to
  // print some diagnostic info
  Serial.begin(9600);
  while (!Serial) {
    // wait for serial line to be ready
  }

  // clear the GLCD screen before starting
  TFTscreen.background(255, 255, 255);
}

void initSD() {
  // try to access the SD card. If that fails (e.g.
  // no card present), the setup process will stop.
  Serial.print("Initializing SD card...");
  if (!SD.begin(sd_cs)) {
    Serial.println("failed!");
    return;
  }
  Serial.println("OK!");

  // initialize and clear the GLCD screen
  TFTscreen.begin();
  TFTscreen.background(255, 255, 255);
}

void writeLifestage() {
  SD.remove("values.txt");
  values = SD.open("values.txt", FILE_WRITE);
  values.println(String(lifestage));
  values.close();
}

void initFiles() {
  Serial.println("values.txt");
  Serial.println(SD.exists("values.txt"));

  if (SD.exists("values.txt")) {
    // open file
    values = SD.open("values.txt", FILE_READ);
    // read from the file until there's nothing else in it:
    while (values.available()) {
      lifestage = values.read();
      Serial.println(lifestage);
    }
    values.close();
  } else {
    //make file
    values = SD.open("values.txt", FILE_WRITE);
    values.println(String(lifestage));
    values.close();
  }
}
