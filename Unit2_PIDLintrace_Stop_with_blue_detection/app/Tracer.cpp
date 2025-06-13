#include "Tracer.h"
#include "ColorSensor.h"
#include <stdio.h>
#include <cstdlib>

Tracer::Tracer():
  leftWheel(EPort::PORT_B,Motor::EDirection::COUNTERCLOCKWISE,true),
  rightWheel(EPort::PORT_A,Motor::EDirection::CLOCKWISE,true),
  colorSensor(EPort::PORT_E) {
}

void Tracer::init() {
  printf("ライントレースを開始します。\n");
}

void Tracer::terminate() {
  printf("走行体を停止します。\n");
  leftWheel.stop();
  rightWheel.stop();
}

void Tracer::run() {
  float turn = calc_pid_value();
  int pwm_l = pwm - turn;
  int pwm_r = pwm + turn;
  leftWheel.setPower(pwm_l);
  rightWheel.setPower(pwm_r);
  
  ColorSensor::RGB rgb;
  colorSensor.getRGB(rgb);
  
  int r = rgb.r;
  int g = rgb.g;
  int b = rgb.b;
  
  float total = r + g + b;
  float blueRatio = b / total;
  
  if (blueRatio > 0.4) {
    printf("青色を検知したため走行体を停止します。\n");
    terminate();
    exit(0);
  }
}

float Tracer::calc_pid_value() {

  const float Kp=0.5;
  const float Ki=0.003;
  const float Kd=0.008;
  const int target=52;

  int current = colorSensor.getReflection();
  float error = current - target;

  integral += error;
  float derivative = error - previousError;
  previousError = error;

  float turn = Kp * error + Ki * integral + Kd * derivative;
  return turn;
}
