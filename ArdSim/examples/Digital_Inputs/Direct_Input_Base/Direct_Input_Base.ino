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

#define BOARD_TYPE   MEGA, 1  // available names - MEGA, UNO, MINI, NANO, numbers 1...9

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

/* input config example: 

    // toggle switch:
    
D5+ sim/systems/avionics_off
D5- sim/systems/avionics_on

    // buttons (on-release or on-push action):
    
D6+ sim/radios/nav1_standy_flip
D7- sim/radios/nav1_standy_flip

*/

