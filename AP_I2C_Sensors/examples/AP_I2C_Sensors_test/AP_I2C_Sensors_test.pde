/*
 *       Example of APM_I2C_SENSORS library.
 *       Code by James Overington
 */


#include <AP_Common.h>
#include <AP_ADC.h>
#include <AP_InertialSensor.h>
#include <math.h>
#include <AP_Progmem.h>
#include <AP_Param.h>
#include <AP_Math.h>
#include <AP_HAL.h>
#include <AP_Buffer.h>
#include <Filter.h>
#include <AP_Baro.h>
#include <AP_GPS.h>
#include <DataFlash.h>
#include <GCS_MAVLink.h>
#include <AP_Notify.h>
#include <AP_Compass.h>
#include <AP_Declination.h>
#include <AP_Airspeed.h>
#include <AP_Vehicle.h>
#include <AP_AHRS.h>
#include <AP_HAL_AVR.h>
#include <AP_HAL_FLYMAPLE.h>
#include <AP_HAL_Linux.h>
#include <AP_HAL_Empty.h>
#include <AP_AHRS.h>
#include <AP_NavEKF.h>
#include <AP_Airspeed.h>
#include <AP_Vehicle.h>
#include <AP_ADC_AnalogSource.h>
#include <AP_Compass.h>
#include <AP_Declination.h>

#include <AP_I2C_Sensors.h>

const AP_HAL::HAL& hal = AP_HAL_BOARD_DRIVER;

AP_I2C_Sensors sensors;

uint32_t timer;

void setup()
{
    hal.console->println("ArduPilot Mega I2C Sensors library test");
    hal.console->println("Initialising...");

    hal.scheduler->delay(100);

    if (!sensors.init()) {
        hal.console->println("Initialisation FAILED\n");
    }
    hal.console->println("Initialisation complete.");
    hal.scheduler->delay(1000);
    timer = hal.scheduler->micros();
}

void loop()
{
    // read values at 10Hz
    if ((hal.scheduler->micros()- timer) > 100000L) {
            sensors.read();

            if (!sensors.healthy) {
                hal.console->println("not healthy");
                return;
            }
            hal.console->print(sensors.results[0]);
            hal.console->print( "\t");
            hal.console->print(sensors.results[1]);
            hal.console->print( "\t");
            hal.console->print(sensors.results[2]);
            hal.console->print( "\t");
            hal.console->print(sensors.results[3]);
            hal.console->print( "\t");
            hal.console->print(sensors.results[4]);
            hal.console->print( "\t");
            hal.console->print(sensors.results[5]);
            hal.console->print( "\t");

            hal.console->println();
            
            timer = hal.scheduler->micros();
    }

    hal.scheduler->delay(1);
}

AP_HAL_MAIN();