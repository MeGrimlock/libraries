/*
Digital nput types basics for ArdSim LAN Library

128 input configuration:
1) 20 digital inputs of Arduino Mega are used to connect 10x10 matrix,
2) all others (28) Arduino pins are used as direct inputs


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
  
InputMatrix(22, 31, 32, 41);  //  Matrix 10x10 (100 inputs - for buttons and switches)

   
  }
  
//--------------------------
void loop() { 

ArdSimScan;  // scan and send all inputs and read data for output


 } 
 //=======================

/* create inputs config file for matrix and direct inputs

input config file sample in_1.cfg:

===================================

    // - the  action for direct inputs:

D3+ sim/systems/avionics_off
D3- sim/systems/avionics_on

D5-  sim/audio_panel/monitor_audio_com2  
D6+ sim/radios/nav1_standy_flip

   // - the  action for matrix inputs:

B1+   sim/electrical/generator_1_on
B1-   sim/electrical/generator_1_off

B2-  sim/audio_panel/monitor_audio_nav1
B3+  sim/radios/com2_standy_flip

===================================

You should see:
    -- for direct inputs:

1) avionics  toggle  switch on the direct input Pin #3  
2) audio panel Com2 toggles on the direct input Pin #5 click (on-release action)
3) Nav1 stby flip  on the  direct button Pin #6 click (on-press action)


    -- for matrix inputs:
5) generator toogle switch on the matrix input  #1
2) Autopilot heading-hold for button on the Pin #2

*/




