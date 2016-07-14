/*

ArdSim I2C connection
This master board is connected to X-Plane (LAN)
and send data to the slave board #2, 3
ARDsim Library used

Download ARDsim Library on the site.

  by Vlad Sychev 2015
http://arduino.svglobe.com
 */

#include <SPI.h>         
#include <Ethernet.h>
#include <ArdSim.h>         // -- include ARDsim library
#include <Wire.h> 

//---- Define Arduino board type and number (optional for single Arduino MEGA board): 
#define BOARD_TYPE   MEGA, 2     //  available names - MEGA, UNO, MINI, NANO, numbers 1...9
  
//---------------------------------------------------------------

void SendOUT(byte s) {SlaveOUT} 

void setup()  { 
  
  ArdSimStart; 

Wire.begin();

InputPin(5);

  
  }
  
//--------------------------
void loop() 
{ 

ArdSimScan;  // scan and send all inputs and read data for output

SendToSlave (3, 6);        // send one dataref to the slave board #3 with I2C
SendToSlave (2, 6, 7, 9, 12);   // send 4 datarefs to the slave board #2 with I2C

// -- Data value  transmitted to the slave only when changed


 } 
 //-------------------------------



