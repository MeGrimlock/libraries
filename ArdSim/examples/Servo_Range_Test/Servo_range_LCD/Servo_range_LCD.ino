/*
Servo  range detection program with LCD output
Vlad S. 2015  arduino.svglobe.com - flight simulator interface 
*/
#include <LiquidCrystal.h>
#include <Servo.h> 

Servo ServoGau;  // servo object #1 
LiquidCrystal Screen(5, NULL, 6, 7, 8, 9, 10); 

int pos = 1500;          // middle position variable  ( 1400-1600 depens on servo model)
int mem;
 
void setup() 
{ 
// pinMode(8, INPUT_PULLUP);        
// pinMode(9, INPUT_PULLUP);  
  
  ServoGau.attach(3);                // attache servo signal on pin 3
  ServoGau.writeMicroseconds(pos);  // set initial position (center)
  
 Screen.clear();                    //clear the LCD during setup
 Screen.begin(16,2);                //define the columns (16) and rows (2)
 Screen.print("Servo microsec:");  
 Screen.noAutoscroll();
} 


void loop() 
{ 
//-  connect potentiometer to analog input #A0 

pos = analogRead(1);
if (abs(pos-mem)>2) { mem=pos;
pos = map(pos, 0, 1023, 540, 2400);
ServoGau.writeMicroseconds(pos); 
Screen.home();   Screen.setCursor(0,1);   Screen.print("         "); 
Screen.setCursor(0,1); Screen.print("   = ");   Screen.print(pos); 
} 
  delay(5);
} 

      

