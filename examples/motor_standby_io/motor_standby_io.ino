#include "WEMOS_Motor.h"

/**
 * Very IMPORTANT: solder the jumper on the back of the shield to IO Standby
 */

int standby_io = D3;

//Motor shiled I2C Address: 0x30
//PWM frequency: 1000Hz(1kHz)
Motor M1(0x30, _MOTOR_A, 1000, standby_io); //Motor A

void setup() {
  Serial.begin(115200);
  Wire.begin();
  M1.begin();
}

void loop() {
  for (int pwm = 40; pwm <= 100; pwm++){
    M1.setMotor( MotorMode::CW, pwm);
    Serial.printf("A:%d%%, B:%d%%, DIR:CW\n", pwm, 100 - pwm);
    delay(500);
    
    M1.setMotor(MotorMode::STANDBY);
    Serial.println("Motor A STANDBY");
    delay(100);
  }
}
