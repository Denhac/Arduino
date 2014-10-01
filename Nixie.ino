# Written by Matthew Saunier (github.com/chunkystew)
# Released under the provisions of the General Public License, Version 3 or greater (at your option)
# You may distribute and modify this code freely under the terms of this license

#include <EEPROM.h>
#include <Wire.h>

#define GPIOADDR 0x20
#define GPIOHOURS 0x13
#define GPIOMINUTES 0x12

int hours = 0;
int minutes = 0;
int seconds = 0;
int cycles = 0;
bool trigger = false;
bool lastTrigger = false;
bool hourSet = false;
bool hourSetLast = false;
bool minuteSet = false;
bool minuteSetLast = false;

void setup(){
  pinMode(10, OUTPUT);
  pinMode(9, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  // Initialize MCP23017
  Wire.begin();
  Wire.beginTransmission(GPIOADDR);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission(); 
  Wire.beginTransmission(GPIOADDR);
  Wire.write(0x01);
  Wire.write(0x00);
  Wire.endTransmission();
  hours = EEPROM.read(0);
  minutes = EEPROM.read(1);}

void loop() { 
 int line = analogRead(0);
 lastTrigger = trigger;
 if(line > 600 && !trigger){trigger = true;}  
 else if(line < 400 && trigger){trigger = false;}
 if(!lastTrigger && trigger){cycles++;}
 if(cycles > 59){
  cycles = 0;
  seconds++;
  if(digitalRead(10) == HIGH){digitalWrite(10, LOW);}
  else{digitalWrite(10, HIGH);}
}
 if(seconds > 59){
  seconds = 0;
  minutes++;
  EEPROM.write(0, hours);
  EEPROM.write(1, minutes);
}
 if(minutes > 59){
  minutes = 0;
  hours++;}
 if(hours > 23){hours = 0;}
 hourSetLast = hourSet;
 if(digitalRead(9) == LOW){hourSet = true;}
 else{hourSet = false;}
 minuteSetLast = minuteSet; 
 if(digitalRead(8) == HIGH){minuteSet = true;}
 else{minuteSet = false;}
 if(hourSet && !hourSetLast){
  hours++;
  seconds = 0;}
 if(minuteSet && !minuteSetLast){
  minutes++;
  seconds = 0;}
 
 
 writeHours(hours);
 writeMinutes(minutes);}

void writeHours(int value){writeGpio(GPIOHOURS, value);}
void writeMinutes(int value){writeGpio(GPIOMINUTES, value);}
void writeGpio(byte address, int value){
  byte tens = value / 10;
  byte ones = value - (tens * 10);
  byte output = 0x00;
  //There is an endianness bug in hardware; fixing it here because laziness.
  output |= tens;
  output |= ones<<4; 
  output = nybbleFlip(output);
  Wire.beginTransmission(GPIOADDR);
  Wire.write(address);
  Wire.write(output);
  Wire.endTransmission();}

byte nybbleFlip(byte input){
 byte output = 0x00;
 if((input & 0x08) == 0x08){output |= 0x01;}
 if((input & 0x04) == 0x04){output |= 0x02;}
 if((input & 0x02) == 0x02){output |= 0x04;}
 if((input & 0x01) == 0x01){output |= 0x08;}
 if((input & 0x80) == 0x80){output |= 0x10;}
 if((input & 0x40) == 0x40){output |= 0x20;}
 if((input & 0x20) == 0x20){output |= 0x40;}
 if((input & 0x10) == 0x10){output |= 0x80;}
 return output;}
