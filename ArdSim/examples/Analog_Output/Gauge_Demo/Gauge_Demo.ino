/*

ArdSim Library Output demonstration
Analog gauge output

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

    //- define coil gauge on the pin #5 (600-2500 is the RPM dataref range)
    
#define RPMA     5, 600, 2500  


void setup() {
  
 ArdSimStart;
   
} 
 
 
void loop() { 
 
 ArdSimScan; 
 

Gauge(7, RPMA);

} 
