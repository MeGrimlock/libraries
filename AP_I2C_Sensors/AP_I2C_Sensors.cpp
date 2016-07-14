/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/*
 *       APM_Sensor.cpp - Arduino Library for Sensor absolute pressure sensor
 *       Code by Jordi Mu�oz and Jose Julio. DIYDrones.com
 *       Sensor is conected to I2C port
 *       Sensor End of Conversion (EOC) pin is PC7 (30)
 *
 *       Variables:
 *               RawTemp : Raw temperature data
 *               RawPress : Raw pressure data
 *
 *               Temp : Calculated temperature (in 0.1�C units)
 *               Press : Calculated pressure   (in Pa units)
 *
 *       Methods:
 *               Init() : Initialization of I2C and read sensor calibration data
 *               Read() : Read sensor data and calculate Temperature and Pressure
 *                        This function is optimized so the main host don�t need to wait
 *                                You can call this function in your main loop
 *                                It returns a 1 if there are new data.
 *
 */

// AVR LibC Includes
#include <inttypes.h>

//#include <AP_Common.h>
//#include <AP_Math.h>            // ArduPilot Mega Vector/Matrix math Library

#include <AP_HAL.h>
#include "AP_I2C_Sensors.h"

extern const AP_HAL::HAL& hal;

#define Sensors_ADDRESS 2 // 


//---------------------------------------------------------------------------------------------------------

  #define HRMI_I2C_ADDR      127
  #define HRMI_HR_ALG        1   // 1= average sample, 0 = raw sample

int getHeartRate(){
  //get and return heart rate
  //returns 0 if we couldnt get the heart rate
  uint8_t i2cRspArray[3]; // I2C response array
  i2cRspArray[2] = 0;
  hal.i2c->writeRegister(HRMI_I2C_ADDR,  0x47, 0x1); // Request a set of heart rate values 
  if (hal.i2c->read(127, 3, i2cRspArray)) {
    return i2cRspArray[2];
  }
  else{
    return 0;
  }
}

void setupHeartMonitor(int type){
  //setup the heartrate monitor
  hal.i2c->begin();
  hal.i2c->writeRegister(HRMI_I2C_ADDR, 0x53, type); // Configure the HRMI with the requested algorithm mode
}
/*
void writeRegister(int deviceAddress, uint8_t address, uint8_t val) {
  //I2C command to send data to a specific address on the device
  hal.i2c.beginTransmission(deviceAddress); // start transmission to device 
  hal.i2c.write(address);       // send register address
  hal.i2c.write(val);         // send value to write
  hal.i2c.end();     // end transmission
}
*/

// Public Methods //////////////////////////////////////////////////////////////

bool AP_I2C_Sensors::read(){	
    // get pointer to i2c bus semaphore
    AP_HAL::Semaphore* i2c_sem = hal.i2c->get_semaphore();
    // take i2c bus sempahore
    if (!i2c_sem->take(HAL_SEMAPHORE_BLOCK_FOREVER))
        return false;
    // We read the calibration data registers
    //if (hal.i2c->read(2, 24, (uint8_t*) results) != 0) {
    results=getHeartRate();
    if ( results != 0) {        
        healthy = false;
        i2c_sem->give();
        return false;
    }
	i2c_sem->give();
	return true;
}

bool AP_I2C_Sensors::init(){
    uint8_t buff[32];    
    // get pointer to i2c bus semaphore
    AP_HAL::Semaphore* i2c_sem = hal.i2c->get_semaphore();
    // take i2c bus sempahore
    if (!i2c_sem->take(HAL_SEMAPHORE_BLOCK_FOREVER))
        return false;
    // We read the calibration data registers
    //hal.i2c->read(ENCODER_ADDRESS, sizeof(buff), buff) 
    /*if (hal.i2c->read(0x47, 32, buff) != 0) {
        healthy = false;
        i2c_sem->give();
        return false;
    }*/
    setupHeartMonitor(HRMI_HR_ALG);
    healthy = true;
    i2c_sem->give();
    return true;
}


