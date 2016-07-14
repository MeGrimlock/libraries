#include "Virtual_Sensor.h"
#include <arduino.h>

Sensor::Sensor(){
  max_amplitude=(random((MAX_AMP-MIN_AMP)*1000)/1000.0)+MIN_AMP;
  min_amplitude=(random((max_amplitude-MIN_AMP)*1000)/1000.0)+MIN_AMP;
  period=random(MIN_PER,MAX_PER);
  period_offset=random(MIN_PER, MAX_PER);
}

void Sensor::setType(sensor_type type){
  output=type;
}

float Sensor::read(){
  switch (output){
    case SINE:
      return (sin(((millis()+period_offset)%period)/(float)period*2.0*PI)+1)/2.0*(max_amplitude-min_amplitude)+min_amplitude;
    break;  
    
    case TRI:
      return abs((((millis()+period_offset)%period)/(float)period*2.0)-1.0) *(max_amplitude-min_amplitude)+min_amplitude;
    break; 
    
    case SAW_RISE:
      return ((millis()+period_offset)%period)/(float)period * (max_amplitude-min_amplitude)+min_amplitude;
    break; 
    
    case SAW_FALL:
      return (1.0-((millis()+period_offset)%period)/(float)period) * (max_amplitude-min_amplitude)+min_amplitude;
    break; 
    
    case RAND:
      return random(min_amplitude*1000,max_amplitude*1000)/1000.0;
    break; 
    
    case SQUARE:
      return round(((millis()+period_offset)%period)/(float)period)*(max_amplitude-min_amplitude)+min_amplitude;
    break; 
  }
}
