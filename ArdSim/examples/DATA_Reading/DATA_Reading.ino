/*

Read dataref values in ArdSim Library
for using in your custom code

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



int Nav1st;   // Nav1 stanby freq.

//---------------------
void setup()  { 
 
   ArdSimStart;   
 
   
  }
  
//--------------------------
void loop()  { 

ArdSimScan; 

 // to get the current dataref value use the GetData function with dataref number
 
 Nav1st = GetData(30);    // read dataref #30 every time, no matter if it changes or not.
 
 
// -- use the NewData function to check if the DataRef has changed.
// This will save program time by ignoring values that remained the same.
 

if (NewData(30)) { 
  
  Nav1st = GetData (30);
  
      // your code 
      }


} 
 //=======================

/*   place  this line in your output config file:

30 0 sim/cockpit2/radios/actuators/nav1_standby_frequency_hz

*/

