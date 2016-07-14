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

// --- define your Arduino IP and(or) X-Plane PC IP addresses (if you have problem with auto-connection):

#define ARDUINO_IP	192,168,1,10      // -- IP of this Arduino (any free IP in your network)
#define XPLANE_IP   192,168,1,8       // -- X-Plane PC IP (should be set as "fixed" in your system)

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


