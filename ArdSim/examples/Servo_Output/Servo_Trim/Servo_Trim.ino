/*

ArdSim Library Output demonstration
Servo output

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

#define BOARD_TYPE   MEGA, 1  //MEGA, UNO, MINI, NANO,  numbers 1..9  


// define  Servo 

#define TrimR    29, 17, -1, 1, 1160, 2000  // pin #17, dataref #29


//---------------------
void setup()  { 
 
   ArdSimStart; 
   

EncoderPin (11, 2);  // Encoder for Rudder Trim

 AnalogIn(1, 1000);   // Or analog pot for Rudder trim
 
} 
 
 
//--------------------------
void loop()  { 

ArdSimScan; 
 
servoGauge (TrimR);   // Rudder Trim Gauge


} //---- End -----

/*
Use test output file  out_N.cfg  included in the ArdRsm Plugin package

In the input config file add these lines:

A1   sim/cockpit2/controls/rudder_trim  -1,1

    // or:

E1+ sim/flight_controls/rudder_trim_right
E1- sim/flight_controls/rudder_trim_left

*/
