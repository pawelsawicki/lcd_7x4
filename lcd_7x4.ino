#define  DIGITS    4
#define  NUMBERS   10
#define  SEGMENTS  7

const byte numbers[] = {
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
const int digits[DIGITS] = { 6, 5, 9, 3 };

const int message[DIGITS] = { 1, 2, 3, 4 };
 
/////////////////////////////////////////////////////////////////////////////////
//
void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin,  OUTPUT);
  
  for (int digit = 0; digit < DIGITS; digit++)
    pinMode(digits[digit], OUTPUT);
}
 
/////////////////////////////////////////////////////////////////////////////////
//
void loop()
{
  for (int digit = 0; digit < DIGITS; digit++) {
    for (int segment = 0; segment < SEGMENTS; segment++) {
      displayOff();
      
      byte bitsToSend = numbers[message[digit]];
      
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
}

void displayOff() {
  for (int digit = 0; digit < DIGITS; digit++)
    digitalWrite(digits[digit], LOW);
}

void displayOn(int digit) {
  if (digit == -1)
      for (int ii = 0; ii < DIGITS; ii++)
        digitalWrite(digits[ii], HIGH);
  else
    digitalWrite(digits[digit], HIGH);
}

