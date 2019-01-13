#include "WEMOS_Motor.h"

//Motor shiled I2C Address: 0x30
//PWM frequency: 1000Hz(1kHz)
Motor M1(0x30,_MOTOR_A, 1000);//Motor A
Motor M2(0x30,_MOTOR_B, 1000);//Motor B


void setup() {
  Serial.begin(115200);
  Wire.begin();
  M1.begin();
  M2.begin();
}

void loop() {
  for (int pwm = 0; pwm <= 100; pwm++){
    M1.setMotor(MotorMode::CCW, pwm);
    M2.setMotor(MotorMode::CCW, 100-pwm);
    Serial.printf("A:%d%%, B:%d%%, DIR:CCW\r\n", pwm, 100-pwm);
    delay(50);
  }
  
  M1.setMotor(MotorMode::STOP);
  M2.setMotor(MotorMode::STOP);
  Serial.println("Motor A&B STOP");
  delay(200);
  
  for (int pwm = 0; pwm <=100; pwm++){
    M1.setMotor(MotorMode::CW, 100-pwm);
    M2.setMotor(MotorMode::CW, pwm);
    Serial.printf("A:%d%%, B:%d%%, DIR:CW\r\n", 100-pwm, pwm);
    delay(50);
  }
  
  M1.setMotor(MotorMode::STOP);
  M2.setMotor(MotorMode::STOP);
  delay(200);
  Serial.println("Motor A&B STOP");

  M1.setMotor(MotorMode::SHORT_BRAKE);
  M2.setMotor(MotorMode::SHORT_BRAKE);
  Serial.println("Motor A&B SHORT BRAKE");  
  delay(1000);
  
  M1.setMotor(MotorMode::STANDBY);//Both Motor standby
  //M2.setmotor( _STANDBY);
  Serial.println("Motor A&B STANDBY");  
  delay(1000);
  
}
