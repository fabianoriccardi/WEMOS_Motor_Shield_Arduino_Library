#include "WEMOS_Motor.h"

#include "Ticker.h"

static Ticker ticker;

static MotorMode lastMode = MotorMode::STANDBY; 
static uint16_t lastPwmVal = 100;
static uint8_t lastMotor=_MOTOR_A;

/**
 * NOTE: this is to solve a bug that blocks the i2c bus if the wemos motor shield doesn't
 * receive any command for more than 10 seconds.
 */
void foo(){
	Wire.beginTransmission(0x30);
	Wire.write(lastMotor | (byte)0x10);
	Wire.write(lastMode);
	Wire.write((byte)(lastPwmVal >> 8));
	Wire.write((byte)lastPwmVal);
	Wire.endTransmission();
}

Motor::Motor(uint8_t address, uint8_t motor, uint32_t freq, uint8_t STBY_IO):
				_address(address), _freq(freq), _STBY_IO(STBY_IO){
	if(motor==_MOTOR_A){
		_motor=_MOTOR_A;
	}else{
		_motor=_MOTOR_B;
	}

	if(_STBY_IO != STBY_IO_UNDEFINED){
		pinMode(_STBY_IO,OUTPUT);
		digitalWrite(_STBY_IO,LOW);
	}
}

bool Motor::begin(){
	setFrequency(_freq);
	return true;
}

void Motor::setFrequency(uint32_t freq){
	Wire.beginTransmission(_address);
	Wire.write(((byte)(freq >> 16)) & (byte)0x0f);
	Wire.write((byte)(freq >> 16));
	Wire.write((byte)(freq >> 8));
	Wire.write((byte)freq);
	Wire.endTransmission();
	ticker.attach(5,foo);
}

void Motor::setMotor(MotorMode mode, float pwm_val){
	uint16_t _pwm_val;
	lastMode = mode;
	lastPwmVal = pwm_val;
	lastMotor = _motor;

	if(_STBY_IO!=STBY_IO_UNDEFINED){
		Serial.println("Standby pin defined!");
		if(mode==MotorMode::STANDBY){
			digitalWrite(_STBY_IO,LOW);
			Serial.println("Standby mode active!!");
			return;
		}else{
			digitalWrite(_STBY_IO,HIGH);
		}
	}
	
	_pwm_val=uint16_t(pwm_val*100);
	if(_pwm_val>10000){
		_pwm_val=10000;
	}

	Wire.beginTransmission(_address);
	Wire.write(_motor | (byte)0x10);
	Wire.write(mode);
	Wire.write((byte)(_pwm_val >> 8));
	Wire.write((byte)_pwm_val);
	Wire.endTransmission();
}