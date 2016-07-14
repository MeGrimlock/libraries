/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
#ifndef __AP_I2C_SENSORS_H__
#define __AP_I2C_SENSORS_H__
#define PRESS_FILTER_SIZE 2
#include <AverageFilter.h>

class AP_I2C_Sensors {
public:
    /* I2C_Sensors public interface: */
    bool            init();
	bool			read();
	bool			healthy;
	int			    results;
};

#endif // __AP_I2C_SENSORS_H__
