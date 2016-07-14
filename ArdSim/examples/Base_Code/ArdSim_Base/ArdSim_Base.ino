/*
Base code for ArdSim LAN Library.
Upload and connect buttons / switches to any 
digital inputs accordingly with your input config file
(Analog pins are not used)

Download ArdSim Library on the site.

  by Vlad Sychev 2015
http://arduino.svglobe.com
 */

#include <SPI.h>         
#include <Ethernet.h>
#include <ArdSim.h>         // -- include ArdSim library
//----------------// MAC-Address of Arduino Ethernet shield:
#define MAC_ADR   0xDE,0xAD,0xBE,0xEF,0xFE,0xED

//----------------------------------------------
//---- Define Arduino board type and number (optional for single Arduino MEGA board): 
#define BOARD_TYPE   MEGA, 1

//-------------------
void setup()  {  
    
 ArdSimStart;
   
  }
//--------------------------
void loop() 
{   

  ArdSimScan;  // scan and send all inputs and read data for output


 } 
 //=======================


