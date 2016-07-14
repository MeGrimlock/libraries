/*
Analog input demonstration
for ArdSim Library (LAN version)

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



#define Throttle1 1        // you can define your constant ...

//---------------------
void setup()  { 
 
   ArdSimStart;    
  
// simple analog input, precision = 100 steps, with full-range pot (0-1024):
    
  AnalogIn(0, 100);  
  
// analog input, precision = 200, pot has value range  10-800  
  
  AnalogIn(Throttle1, 200, 10, 800);

// use analog inputs as additional digital inpus:
 
  AnalogSwitch(2, 2);   // simple toggle switch (2-positions),  pin A2
  AnalogSwitch(3, 5, 5);  //  5-position switch (or 5-buttons), pin A3
  AnalogSwitch(4, 6);  //  6-position switch, pin A4
   
/*  !!  Comment or delete lines with unused Analog inputs 
		to prevent scanning open inputs and unintentional
		sending the input interference data    */

InputPin(NOINPUT);

  }
  
//--------------------------
void loop()  { 

ArdSimScan; // scan and send all inputs and read data for output


 } 
 //===== end =============


/* 
input config file sample in_1.cfg:

===================================

A0  sim/cockpit2/engine/actuators/cowl_flap_ratio   0,1   1 
A1  sim/cockpit2/engine/actuators/throttle_ratio   0,1   1

    // - simple switch on the inputs A2:
    
A2/1   sim/electrical/generator_1_on
A2/2   sim/electrical/generator_1_off

	// -- multi-position switches:

A3/1 sim/magnetos/magnetos_off_1
A3/2 sim/magnetos/magnetos_right_1   
A3/3 sim/magnetos/magnetos_left_1
A3/4 sim/magnetos/magnetos_both_1
A3/5 sim/starters/engage_starter_1 

A4/1  sim/transponder/transponder_off
A4/2  sim/transponder/transponder_standby
A4/3  sim/transponder/transponder_alt   
A4/4  sim/transponder/transponder_test
A4/5  sim/transponder/transponder_on
A4/6  sim/transponder/transponder_ground

===================================

You get:

1) cowl flap handle on the A0 input, full pot range is used
2) throttle handle on the A1 input, partial pot range is used
3) simple toggle switch on the A2 input - generator on/off
5) 5-position switch on the A3 input for magneto/starter
5) 6-position switch on the A4 input for KT-70 Transponder mode

*/




