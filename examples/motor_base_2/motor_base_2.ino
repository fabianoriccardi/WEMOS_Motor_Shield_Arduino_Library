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
  Serial.println("Test PWM 30 to 100, step 0.1, CW");
  for (float pwm = 30; pwm <= 100; pwm+=0.1){
    M1.setMotor( MotorMode::CW, pwm);
    Serial.println(pwm);
    delay(100);
  }
  
  M1.setMotor(MotorMode::STOP);
  Serial.println("Motor A STOP");
  delay(1000);
  
  Serial.println("Test PWM 30 to 100, step 0.1, CCW");
  for (float pwm = 30; pwm <= 100; pwm+=0.1){
    M1.setMotor(MotorMode::CCW, pwm);
    Serial.println(pwm);
    delay(100);
  }
  
  M1.setMotor(MotorMode::STOP);
  Serial.println("Motor A STOP");

  delay(1000);
}
