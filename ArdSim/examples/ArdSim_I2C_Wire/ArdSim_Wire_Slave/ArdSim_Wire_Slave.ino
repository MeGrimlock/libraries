/*

ArdSim I2C connection.

This slave board is receiving data from master board connected to X-Plane (LAN)
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
//---------------------------------------------------------------

#define Flaps   0, 0, 1, 560, 2100 

void setup()  { 
  
  ArdSimSlave(20);    // init,  board I2C number 20

 OutputPin(5,12);


  }
  
//--------------------------
void loop() 
{ 




servoGauge (6, Flaps); 


 } 

