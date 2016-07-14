/*

ArdSim I2C connection
This master board is connected to X-Plane (LAN)
and send data to the slave board #20
ArdSim Library used

Download ArdSim Library on the site.

  by Vlad Sychev 2015
http://arduino.svglobe.com
 */

#include <SPI.h>         
#include <Ethernet.h>
#include <ArdSim.h>         // -- include ArdSim library
#include <Wire.h>

//---- Define Arduino board type and number (optional for single Arduino MEGA board): 
#define BOARD_TYPE   MEGA, 2     //  available names - MEGA, UNO, MINI, NANO, numbers 1...9

//---------------------------------------------------------------

void setup()  {  
  
  ArdSimStart; 

  
  }
  
//--------------------------
void loop() 
{ 

ArdSimScan;  // scan and send all inputs and read data for output


SendToSlave(20, 6);   // send dataref #6 to the slave board with I2C address 20

// -- Data value  transmitted to the slave only when changed


 } 

