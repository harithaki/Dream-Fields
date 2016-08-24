/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

#include <EEPROM.h>

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  int val = EEPROM.read(50);

  if(val != 1){
  digitalWrite(8, HIGH);
  digitalWrite(7, LOW);// turn the LED on (HIGH is the voltage level)
  EEPROM.write(50, 1);
  delay(2000);              // wait for a second
   digitalWrite(8, LOW);
  }

delay(4000);  
  if(val == 1){
  digitalWrite(8, LOW); 
  digitalWrite(7, HIGH);// turn the LED off by making the voltage LOW
  EEPROM.write(50, 0);
  delay(2000); 
  digitalWrite(7,LOW);// wait for a second
  }
 delay(4000);  
}
