#include <Time.h>

#define  SECTORS    4
#define  SEGMENTS   7
#define  DIGITS     10

const byte digits[] = {
  B00111111,
  B00000110,
  B01011011,
  B01001111,
  B01100110,
  B01101101,
  B01111101,
  B00000111,
  B01111111,
  B01101111
};
 
//// Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 8;
//// Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 12;
//// Pin connected to Data in (DS) of 74HC595
const int dataPin  = 11;
//// Pin connected to display's common annode
const int sectors[SECTORS] = { 6, 5, 9, 3 };

int message[SECTORS];

int counter = 0;
 
/////////////////////////////////////////////////////////////////////////////////
//
void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin,  OUTPUT);
  
  for (int __sector = 0; __sector < SECTORS; __sector++)
    pinMode(sectors[__sector], OUTPUT);
}
 
/////////////////////////////////////////////////////////////////////////////////
//
void loop()
{
  
  /*
  for (int digit = 0; digit < DIGITS; digit++) {
    for (int segment = 0; segment < SEGMENTS; segment++) {
      displayOff();
      
      byte bitsToSend = digits[message[digit]];
      
      bitsToSend = bitsToSend & (B00000001 << segment); // top row
   
      bitsToSend = bitsToSend ^ B11111111; // inversion - common anode
   
      // turn off the output so the pins don't light up
      // while you're shifting bits:
      digitalWrite(latchPin, LOW);
   
      // shift the bits out:
      shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);
   
      digitalWrite(latchPin, HIGH);
      displayOn(digit);
      delayMicroseconds(500);
    }
  }
  */

  counter = millis()/1000;

  message[3] = counter % 10;
  message[2] = (counter / 10 ) % 10;
  message[1] = (counter / 100 ) % 10;
  message[0] = (counter / 1000 ) % 10;
  
  for (int __sector = 0; __sector < SECTORS; __sector++) {
    displayUpdate(__sector);
    delay(2);
  }
}

void displayUpdate(int sector) {
  for (int __sector = 0; __sector < SECTORS; __sector++) {
    digitalWrite(sectors[__sector], LOW);

/*
    digitalWrite(latchPin, LOW);
    digitalWrite(latchPin, HIGH);
 
    delayMicroseconds(100);
*/

    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, ~B00000000);
    shiftOut(dataPin, clockPin, MSBFIRST, ~digits[message[sector]]);
    digitalWrite(latchPin, HIGH);

    digitalWrite(sectors[sector], HIGH);
  }
}
