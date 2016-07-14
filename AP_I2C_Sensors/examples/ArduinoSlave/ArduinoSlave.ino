// Wire Slave Sensor Sender
// by James Overington

// Sends data from 6 virtual sensors for reciept by suitably modified ArduXXX code on APM 
// Created 20 March 2014
// This example code is in the public domain.

#include <Wire.h>
#include "Virtual_Sensor.h"

Sensor sensors[6];
float data[6];

void setup()
{
  randomSeed(analogRead(0));

  //Set sensor types:
  sensors[0].setType(SINE);
  sensors[1].setType(TRI);
  sensors[2].setType(SAW_RISE);
  sensors[3].setType(SAW_FALL);
  sensors[4].setType(RAND);
  sensors[5].setType(SQUARE);
 
  Wire.begin(2);                // join i2c bus with address #2 (#2 arbitarily selected but must match setting in ArduXXX code and not conflict with any other device on the bus)
  Wire.onRequest(requestEvent); // register event
}

void loop()
{
  data[0]=sensors[0].read();
  data[1]=sensors[1].read();
  data[2]=sensors[2].read();
  data[3]=sensors[3].read();
  data[4]=sensors[4].read();
  data[5]=sensors[5].read();
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  Wire.write((uint8_t *)&data,24); // respond with message of 24 bytes
}                                   // as expected by master
