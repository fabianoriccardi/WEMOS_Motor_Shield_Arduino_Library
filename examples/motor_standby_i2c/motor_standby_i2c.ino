#include "WEMOS_Motor.h"

//Motor shiled I2C Address: 0x30
//PWM frequency: 1000Hz(1kHz)
Motor M1(0x30, _MOTOR_A, 1000);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  M1.begin();
}

void loop() {
  for (int pwm = 50; pwm <= 60; pwm++){
    M1.setMotor( MotorMode::CW, pwm);
    Serial.printf("A:%d%%, DIR:CW\r\n", pwm);
    delay(2000);
    M1.setMotor(MotorMode::STANDBY);
    Serial.println("Motor A STANDBY");
    delay(100);
  }
}
