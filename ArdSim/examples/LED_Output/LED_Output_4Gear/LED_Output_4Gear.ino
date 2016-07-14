/*
ArdSim Library Output demonstration
4 LED outputs controlled with gear datarefs. 

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

  // define 4 LED connections ( first number - Arduino pin, second is dataref number

#define  Gear1   5, 1     // { 5 = LED pin number 1 = dataref number (can be found in you out_1,cfg list)
#define  Gear2   6, 2  				
#define  Gear3   7, 3  
#define  GearTransit   8, 4 

//---------------------
void setup()  { 
 
   ArdSimStart;   


}
//--------------------------
void loop()  { 

ArdSimScan; 


   LEDout(Gear1);  
   LEDout(Gear2);    
   LEDout(Gear3); 
   LEDout(GearTransit);    
   
   
} 

//--- End -------------------

/* output config file out_1.cfg:

===================================

1 1 sim/flightmodel2/gear/deploy_ratio 1
2 1 sim/flightmodel2/gear/deploy_ratio 2
3 1 sim/flightmodel2/gear/deploy_ratio 3
4 0 sim/cockpit2/annunciators/gear_unsafe
===================================

You should see:
1) LED on pin #5 will be On when the 1st gear is full down
2) LED on pin #6 will be On when the 2nd gear is full down   
3) LED on pin #7 will be On when the 3rd gear is full down 
4) LED on pin #8 will be On while all gear unsafe 

*/




