/*
Use your custom code conditions 
to send  direct UDP commands?datarefs to X-Plane

for ArdSim Library (LAN version only)
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

//---------------------
int condition1;
int condition2;
int condition3;


void setup() {

 ArdSimStart;


}
  
//--------------------------
void loop() { 
  
 ArdSimScan; 

/* 
Send commans/datarefs to X-Plane from your custom code 
without using input config file (direct UDP input):

XPDref ("dataref", value)    -- send dataref with value
XPCmnd ("command")           -- send command
XPMenu (menu_number))        -- open menu #
XPCmnd ("letter")            -- send keyboard symbol


      Examples:
*/


// direct dataref value set:

if ( condition1 )        XPDref ("cockpit2/radios/actuators/hsi_obs_deg_mag_pilot", 180); 
  
// - Menu item - "Forwards view with HUD", #1801:

if (ReadInput(2, ON ))   XPMenu (1801);   // set menu if pin #2 state was changed to "On"
  
//- direct command input:

if ( condition2 )   XPCmnd ("sim/systems/avionics_on");
  
//- keyboard letter emulation input:

if ( condition1 )   XPCmnd ("g");      // toggle gear

} 
//--- End -------------------
