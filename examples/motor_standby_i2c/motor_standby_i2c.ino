#include "WEMOS_Motor.h"

//Motor shiled I2C Address: 0x30
//PWM frequency: 1000Hz(1kHz)
Motor motor(0x30, _MOTOR_A, 1000);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  motor.begin();
}

void loop() {
  for (int pwm = 50; pwm <= 60; pwm++){
    motor.setMotor( MotorMode::CW, pwm);
    Serial.printf("A:%d%%, DIR:CW\r\n", pwm);
    delay(2000);
    motor.setMotor(MotorMode::STANDBY);
    Serial.println("Motor A STANDBY");
    delay(100);
  }
}
