/*
Read any direct or matrix input state
or detect input state change  for use
in your custom code

Don't use this for sending data to X-Plane with the SimInput function ("C" pin name prefix) -
it is already done automatically using the "D"-prefix.

ArdSim Library (LAN version)
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


//----------------------
void setup() {

 ArdSimStart;

InputMatrix(22, 23, 24, 25);   //connect button matrix 2x2


}
  
//--------------------------
void loop() { 
  
 ArdSimScan; 
 

  // check if Pin #2 state is changed from OFF to ON:
   
if (ReadInput(2, ON ))  {   } // your code here

  // check if matrix butoon #2 state is changed from ON to OFF:
  
if (ReadInput(2, OFF, MX))  {   } // your code here                                     

//-------------------------------------------
// Read the current Arduino Pin #3   state change (dynamics)

int act = ReadInput( 3, ON ); // check if Pin #3 state is changed from 0 to 1 and save

if (act==1)  { }// do something 

//=============== STATIC ===================

// Read the current Arduino Pin #5 STATIC state for use in your custom code
// see  description on the site

if (ReadInput (5)==1) {   }  // your code here if pin state is "ON"
else     { } // your "else" code here  (pin state is static "OFF"

// Read static state of the matrix input #5:

int mx5 = ReadInput (5, MX);

// Read static state of the matrix input #67 
// (MX can be omited if node number more than 53 for MEGA or 13 for UNU:

int mx67 = ReadInput (67); 

} 
//--- End -------------------

