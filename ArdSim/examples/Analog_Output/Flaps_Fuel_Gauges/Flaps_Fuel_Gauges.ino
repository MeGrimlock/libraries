/*

ArdSim Library Output demonstration
Analog gauge outputs

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

 // define Analog Gauges

#define Flaps     5, 0, 1        // Flaps gauge on pin #5
#define Fuel1     6, 10, 300     // -- fuel 1 (10-300 kgs)  - pin #6
#define Fuel2     7, 10, 300     // -- fuel 2 (10-300 kgs)   - pin #7


void setup()  {
 
 ArdSimStart;   //-- ArdSim initialization

}

//=================================================
void loop() { 
 
 ArdSimScan; 

   
Gauge(6, Flaps);     // flaps controlled with dataref #6
            
Gauge(9, Fuel1);     // dataref #9 (in the in_1.cfg file)
Gauge(10, Fuel2);    // dataref #10


 }   //-- End-----------------

