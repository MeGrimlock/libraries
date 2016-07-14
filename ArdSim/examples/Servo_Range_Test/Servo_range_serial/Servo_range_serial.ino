
#include <LiquidCrystal.h>
#include <Servo.h> 
Servo ServoGau;  // servo object #1 

int pos = 1500;          // middle position variable  ( 1400-1600 depens on servo model)
int mem;
 
void setup() 
{ 
 pinMode(8, INPUT_PULLUP);        
 pinMode(9, INPUT_PULLUP);  
  
  ServoGau.attach(17);                // attache servo signal on pin 3
  ServoGau.writeMicroseconds(pos);  // set initial position (center)
  
Serial.begin(57600);  
} 

void loop() 
{ 
//-  connect potentiometer to analog input #A0

pos = analogRead(0)*2;
if (abs(pos-mem)>2) { mem=pos;
pos = map(pos, 2040, 5, 400, 2300);
ServoGau.writeMicroseconds(pos); 

     Serial.println(pos); Serial.println();   
  delay(5); }
} 

      

