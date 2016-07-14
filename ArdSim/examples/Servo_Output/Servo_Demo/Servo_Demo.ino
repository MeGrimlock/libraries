/*

ArdSim Library Output demonstration
Servo output, non-linear servo output

Download ArdSim Library on the site.

  by Vlad Sychev 2015
http://arduino.svglobe.com
 */

#include <SPI.h>         
#include <Ethernet.h>
#include <ArdSim.h>         // -- include ARDsim library

//----------------// MAC-Address of Arduino Ethernet shield:
#define MAC_ADR   0xDE,0xAD,0xBE,0xEF,0xFE,0xED

//----------------------------------------------
//---- Define Arduino board type and number (optional for single Arduino MEGA board): 

#define BOARD_TYPE   MEGA, 1  //MEGA, UNO, MINI, NANO,  numbers 1..9  

// define 3 Servo connections

#define Flap     6,  12, 0, 1, 500, 2150      // servo on pin #12, dataref #6
#define Amp     25, 41, 0, 100, 560, 2150    // servo on pin #41, dataref #25

// --- define ONE servo for 3-section gauge:

  // servo on pin #11, dataref #7
#define   RPM1   7,  11,    0,    1300,  600,  1067
#define   RPM2   7,  11,   1301, 2000,  1068, 1734
#define   RPM3   7,  11,   2001, 2300,  1735, 2030



//---------------------
void setup()  {  //Serial.begin(115200);
 
   ArdSimStart; 


} 
 
//--------------------------
void loop()  { 

ArdSimScan; 
 

servoGauge (Flap);

servoGauge (RPM1 );
servoGauge (RPM2 );
servoGauge (RPM3 );



}
//-------------------------------------------------

/*
Use test output file  out_N.cfg  included in the ArdRsm Plugin package
*/
