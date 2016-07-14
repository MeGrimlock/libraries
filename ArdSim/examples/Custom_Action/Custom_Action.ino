/*
Use your custom code conditions 
to send  commands for input

for ArdSim Library (LAN version)
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

//---------------------


void setup() {

 ArdSimStart;


}
  
//--------------------------
void loop() { 
  
 ArdSimScan; 

// Send commans/datarefs to X-Plane from your custom code 
   
      {  // your custom code here

          // you can check some code conditions and send  command C7:
  
          SimInput(7);                                       
      }


} 
//--- End -------------------

/* input config file in_1.cfg:
===================================

C7 sim/radios/nav1_standy_flip
===================================

*/
