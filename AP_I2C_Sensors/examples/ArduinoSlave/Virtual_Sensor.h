#define MIN_AMP 0.0     //minimum amplitude
#define MAX_AMP 10.0    //maximum amplitude
#define MIN_PER 1000    //minimum period in ms
#define MAX_PER 10000   //maximum period in ms

enum sensor_type {
  SINE,                 //sine wave
  TRI,                  //triangle wave
  SAW_RISE,             //sawtooth rising wave
  SAW_FALL,             //sawtooth falling wave
  RAND,                 //random wave
  SQUARE                //square wave
};

class Sensor{

private:
  float min_amplitude;
  float max_amplitude;  
  long period;
  int period_offset;
  sensor_type output;

public:
  Sensor();
  
  void setType(sensor_type type);
  
  float read();
}; //class Sensor