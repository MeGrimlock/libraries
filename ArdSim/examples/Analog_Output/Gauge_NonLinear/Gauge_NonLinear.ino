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

     //---define  gauge on the pin #5 for two sectors
     
#define RPMA1     5, 600, 1300, 0, 40          //   (600-1300  range in 0-40% of scale)
#define RPMA2     5, 1301, 2500, 41, 100       //   (1300-2500  range in 41-100% of scale)

void setup() {

 ArdSimStart; 
   

} 
 
 
void loop() 
{ 
 
 ArdSimScan; 
 

Gauge(7, RPMA1);
Gauge(7, RPMA2);

} 
