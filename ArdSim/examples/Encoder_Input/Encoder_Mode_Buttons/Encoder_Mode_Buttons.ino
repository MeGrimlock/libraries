/*

Encoder Mode change buttons for encoder #5 (E5).
Ue 3 external buttons connected directly to 3 Arduino pins
and 5 encoders (direct connection).

You can connect only E5 encoder to tect, but all setup lines should be intact.
You can use this sample for Encoder matrx (port), adding the "EncoderPort" function

For this demo use the test input config file below on this page
and incuded in ArdSim Plugin package.
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

//-----------------------
void setup() {

 ArdSimStart;

      // Direct encoders connetion (E1...E4), 
      
EncoderPin (30);     // encoder #1 (E1) - pins #30,32, no button
EncoderPin (25);     // encoder #2 (E2) - pins #25,26, no button
EncoderPin (22, 4);   // encoder #3 (E3) - pins #22,23,24, (4-mode click button)
EncoderPin (7, 1);   // Encoder #4 (E4) - pins #7,8,9, button mode =1 (hold mode)  
EncoderPin (28);      // encoder #5 (E5) - pins #28,29   

  }
  
//--------------------------
void loop()   { 
  
ArdSimScan;


    // Assign three mode buttons for encoder #5 ( 

EncModeBtn (18, 5, 'A');  // button on the pin #18 set encoder E4 to mode "A"
EncModeBtn (19, 5, 'H');  // button on the pin #19 set encoder E4 to mode "H"
EncModeBtn (20, 5, 'V');  // button on the pin #20 set encoder E4 to mode "V"


 } 
//--- End -------------------

/* input test config file in_N.cfg - replace "N" with your board number
   (included in the ArdSim Plugin package)

===================================
 
  //  Encoder #5 has  three external mode buttons (on pins 5,6,7)

E5/A+ sim/autopilot/airspeed_up
E5/A- sim/autopilot/airspeed_down
E5/H+ sim/autopilot/heading_up
E5/H- sim/autopilot/heading_down
E5/V+ sim/autopilot/vertical_speed_up
E5/V- sim/autopilot/vertical_speed_down

===================================

You will get:

1) Encoder #1 simply changes the HSI OBS course (no mode buttons)

2) Encoder #2  changes the Barometer value  (no mode buttons)

3) Encoder #3 changes transponder "ones-tens-hundreds-thousands 
  changing mode in cycle when its buil-in button is clicked
  
4) Encoder #4 set Nav1 "coarse" frequency when its built-in button is not pressed,
    and Nav1 "fine"  frequency when its  button is  pressed and held
    
5) Encoder #5 has three modes switched with 3 preselected buttons:
    1st button change mode to 'A' - autopilot airspeed change
    2nd button change mode to 'H' - autopilot heading change
    3rd button change mode to 'V' - autopilot vertical speed change


*/

