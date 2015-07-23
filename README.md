# Ardogotchi
Tamagotchi clone on the Arduino platform

This program loads and displays a bitmap onto an arduino compatible TFT LCD screen v1.7 includes lifestages for the tamagotchi
and supports a temperature sensor to mimick good conditions to hatch faster, number of lifes, feeding and dying. Also included 
is a push button to feed the tamagotchi to prevent it from dying. It is writen in C (arduino).

You will need:
- Arduino uno
- TFT LCD (http://arduino.cc/en/Guide/TFT)
- TFT LCD Connector cable (or home made connector)
- 1x NO push button
- 1x NTC Thermistor
- 2x Resistor (depending on type of thermistor) 
- 1x micro sd (to store the bitmaps)
- Arduino IDE to load the code (https://www.arduino.cc/en/Main/Software)

How to connect the LCD screen
![alt tag](https://github.com/JeroenPleysier/Ardogotchi/blob/master/Pinout/LCD.jpg)

How to connect the button & ntc
![alt tag](https://github.com/JeroenPleysier/Ardogotchi/blob/master/Pinout/Button%20and%20NTC.png)
