#include "WEMOS_Motor.h"

#include "Ticker.h"

static Ticker ticker;

static MotorMode lastMode = MotorMode::STOP; 
static uint16_t lastPwmVal = 100;
static uint8_t lastMotor=_MOTOR_A;

/**
 * NOTE: this is to solve a bug that blocks the i2c bus if the wemos motor shield doesn't
 * receive any command for more than 10 seconds.
 */
void foo(){
    //Repeat last command
    Wire.beginTransmission(0x30);
    Wire.write(lastMotor | (byte)0x10);
    Wire.write(lastMode);
    Wire.write((byte)(lastPwmVal >> 8));
    Wire.write((byte)lastPwmVal);
    Wire.endTransmission();
    if(__WEMOS_MOTOR_DEBUG) Serial.println("Ho aggiornato il motore");
}

Motor::Motor(uint8_t address, uint8_t motor, uint32_t freq, uint8_t STBY_IO, uint8_t resetPin, bool enableAutoUpdate):
				_address(address), _freq(freq), _STBY_IO(STBY_IO), _resetPin(resetPin), enableAutoUpdate(enableAutoUpdate){
	if(motor==_MOTOR_A){
		_motor=_MOTOR_A;
	}else{
		_motor=_MOTOR_B;
	}

	if(_STBY_IO != STBY_IO_UNDEFINED){
		pinMode(_STBY_IO,OUTPUT);
		digitalWrite(_STBY_IO,LOW);
	}

	if(_resetPin!=UNDEFINED_PIN){
		pinMode(_resetPin,OUTPUT);
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

    // NOTE: this introduce a concurrency problem: Wire is not thread safe!
	if(enableAutoUpdate){
        ticker.attach(4,foo);  
    }
}

void Motor::setMotor(MotorMode mode, float pwm_val){
	uint16_t _pwm_val;
	lastMode = mode;
	lastPwmVal = pwm_val;
	lastMotor = _motor;

	if(_STBY_IO!=STBY_IO_UNDEFINED){
		if(__WEMOS_MOTOR_DEBUG) Serial.println("Standby pin defined!");
		if(mode==MotorMode::STANDBY){
			digitalWrite(_STBY_IO,LOW);
			if(__WEMOS_MOTOR_DEBUG) Serial.println("Standby mode active!!");
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

void Motor::forceUpdate(){
  foo();
}

void Motor::reset(){
	if(_resetPin!=UNDEFINED_PIN){
	  if(__WEMOS_MOTOR_DEBUG) Serial.println("[WEMOS MOTOR] resetting");
	  digitalWrite(_resetPin,LOW);
	  delay(5);
	  digitalWrite(_resetPin,HIGH);
	  delay(10);
	}else{
      if(__WEMOS_MOTOR_DEBUG) Serial.println("[WEMOS MOTOR] You have to set the reset pin");
    }
}