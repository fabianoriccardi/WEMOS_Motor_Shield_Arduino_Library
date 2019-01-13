
#ifndef __WEMOS_MOTOR_H
#define __WEMOS_MOTOR_H


#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "Wire.h"

#define _MOTOR_A 0
#define _MOTOR_B 1

#define STBY_IO_UNDEFINED 255

enum MotorMode { SHORT_BRAKE = 0, CCW = 1, CW = 2, STOP = 3, STANDBY = 4};

class Motor{
public:
	
	
	Motor(uint8_t address, uint8_t motor, uint32_t freq, uint8_t STBY_IO = STBY_IO_UNDEFINED);

	/**
	 * Init the motor shield
	 */
	bool begin();
	
	/* 
	 * Set motor

motor:
	_MOTOR_A	0	Motor A
	_MOTOR_B	1	Motor B

dir:
	_SHORT_BRAKE	0
	_CCW			1
	_CCW			2
	_STOP			3
	_STANDBY		4

pwm_val:
	0.00 - 100.00  (%)
*/
	void setMotor(MotorMode mode, float pwm_val = 100);

private:
	uint8_t _address;
	uint8_t _motor;
	uint32_t _freq;
	uint8_t _STBY_IO;

	/**
	 * Set the pwm frequency
	 */
	void setFrequency(uint32_t freq);

};


#endif

