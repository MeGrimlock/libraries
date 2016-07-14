/*
ArdSim Input Mode demonstration
"Matrix"  inputs demo.

1) Set 3x3 pins for key matrix input (used for buttons or toggles)
and set repeat modes for two buttons connected to the  matrix nodes B5, B6.

2)  set repeat modes for two direct input buttons connected to the pins #5, #6.

For thids demo use the input config file below on this page.

ArdSim Library is used, download last version on the site.
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

//-----------------------------
void setup() {

 ArdSimStart;

InputPin(11, 12); InputPin(42, 43);  // define pins #11-2 and 42-43 for direct input

InputMatrix(22, 24, 25, 27);   //connect switch matrix 3x3 (inpus B1....B9 )

RepeatBtn(11);          // - continued action for button on  PIN #11 ("on-hold")
RepeatBtn(12, HOLD);     // - repeated action for button #12 ("click and hold))


RepeatBtn(4, MX);          // - continued action for matrix button B4 ("on-hold")
RepeatBtn(5, HOLD, MX);     // - repeted action for button B5 ("click and hold))

RepeatBtn(42, HOLD);      // - repeated action for button #42 ("click and hold)
RepeatBtn(43, HOLD);     // - repeated action for button #43 ("click and hold)

}
//--------------------------

void loop()   { 
  
ArdSimScan;
                               

  } 

//--- End -------------------

/*  input config file lines (in_1.cfg):

===================================

D11+  sim/annunciator/test_all_annunciators
D12+  sim/radios/obs_HSI_up

    // - the same action for buttons on the pins #11,12:
    
B4+  sim/starters/engage_starter_1
B5+  sim/autopilot/heading_up

D42+ sim/flight_controls/pitch_trim_down
D43+ sim/flight_controls/pitch_trim_up

===================================

You should see: 

1) continued test for annunciators on the button Pin #11 (push and hold)
2) OBS HSI up by one step or repeat after 1 sec hold   on butoon Pin #12
3) Start engine on the matrix button #4 push and hold
4) autopilot heading up by one step or repeat after 1 sec hold on the matrix butoon #5 


*/




