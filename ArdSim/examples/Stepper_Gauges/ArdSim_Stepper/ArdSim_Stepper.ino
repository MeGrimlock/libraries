/*

Stepper code for ArdSim  Library.

For X25 alike steppers with the limiter

Download ArdSim Library on the site.

Download ArdSim Library on the site.

  by Vlad Sychev 2015
http://arduino.svglobe.com
 */

#include <SPI.h>    
#include <Ethernet.h>
#include <ArdSim.h>         // -- include ArdSim library
//----------------// MAC-Address of Arduino Ethernet shield:
#define MAC_ADR   0xDE,0xAD,0xBE,0xEF,0xFE,0xED
//---------------------------------------------------------------

// --- define your PC and Arduino IP addresses (if you have problem with auto-connection):
#define ARDUINO_IP  192,168,1,5               // -- IP of this Arduino (only the last quarter!)
//#define XPLANE_IP 192,168,1,20      // -- X-Plane PC IP address

#define BOARD_TYPE    MEGA, 1

//------ define parameters: (1 - number of dataref, 2 - minimum dataref value, 3 - max dataref value )

#define RPM1   7, 0, 2600     // RPM #1 , dataref #7, range  0...2600 RPM
#define Flaps  6, 0,1          // Flaps position, dref #6, range   0 - 1.0

void setup()
  { 
    
 ArdSimStart;

/* Assign steppers: 1 - pin number for stepper input #1
                    2 - pin number for stepper input #4   
                    3 - pin number for stepper inputs #2 and #3
                    4 - defined parameter.
                                                      */
  StepGauge(5, 6, 7, RPM1);
  StepGauge(22, 23, 24, Flaps );

 }
  
//--------------------------
void loop() { 

  ArdSimScan;  // scan and send all inputs and read data for output


 } 
 //=======================


