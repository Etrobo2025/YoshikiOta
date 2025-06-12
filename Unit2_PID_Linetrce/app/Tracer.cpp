#include "Tracer.h"
#include <stdio.h>

Tracer::Tracer():
  leftWheel(EPort::PORT_B,Motor::EDirection::COUNTERCLOCKWISE,true),
  rightWheel(EPort::PORT_A,Motor::EDirection::CLOCKWISE,true),
  colorSensor(EPort::PORT_E) {
}

void Tracer::init() {
  printf("Tracer\n");
}

void Tracer::terminate() {
  printf("Stopped.\n");
  leftWheel.stop();
  rightWheel.stop();
}

void Tracer::run() {
  float turn = calc_pid_value();
  int pwm_l = pwm - turn;
  int pwm_r = pwm + turn;
  leftWheel.setPower(pwm_l);
  rightWheel.setPower(pwm_r);
}

float Tracer::calc_pid_value() {

  const float Kp=0.67;
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
