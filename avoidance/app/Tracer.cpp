#include "Tracer.h"
#include "ColorSensor.h"
#include "UltrasonicSensor.h"
#include "Clock.h"
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>

using namespace spikeapi;

Tracer::Tracer() :
  leftWheel(EPort::PORT_B, Motor::EDirection::COUNTERCLOCKWISE, true),
  rightWheel(EPort::PORT_A, Motor::EDirection::CLOCKWISE, true),
  colorSensor(EPort::PORT_E),
  ultrasonic(EPort::PORT_F)
{
}

void Tracer::init() {
  printf("ライントレース初期化完了。\n");
}

void Tracer::terminate() {
  printf("停止処理を行います。\n");
  leftWheel.stop();
  rightWheel.stop();
}

void Tracer::run() {
  Clock clock;
  
  int32_t distance = ultrasonic.getDistance();
  
if (distance <= 0 || distance > 400) {
    distance = 400;
}

    if (distance < 150) {
        printf("障害物検知で停止します。\n");
        int mpower = 50;
        const uint32_t duration = 1000000;
        while(1){
                leftWheel.stop();
                rightWheel.stop();
                clock.sleep(1000000);
                
                leftWheel.setPower(-mpower);
                rightWheel.setPower(-mpower);
                clock.sleep(500000);
                
                leftWheel.setPower(mpower);
                rightWheel.stop();
                clock.sleep(duration);
                
                leftWheel.setPower(mpower);
                rightWheel.setPower(mpower);
                clock.sleep(800000);
                
                leftWheel.stop();
                rightWheel.setPower(mpower);
                clock.sleep(1500000);
                
                leftWheel.setPower(mpower);
                rightWheel.setPower(mpower);
                clock.sleep(500000);
                
                leftWheel.stop();
                rightWheel.setPower(mpower);
                clock.sleep(1500000);
                
                leftWheel.setPower(mpower);
                rightWheel.setPower(mpower);
                clock.sleep(1000000);
                
                 leftWheel.setPower(mpower);
                rightWheel.stop();
                clock.sleep(duration);
                break;
                
          }
    }
  
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
    printf("青色を検知：停止します。\n");
    terminate();
    exit(0);
  }
}
float Tracer::calc_pid_value() {
  const float Kp = 0.5;
  const float Ki = 0.003;
  const float Kd = 0.008;
  const int target = 52;

  int current = colorSensor.getReflection();
  float error = current - target;

  integral += error;
  float derivative = error - previousError;
  previousError = error;

  float turn = Kp * error + Ki * integral + Kd * derivative;
  return turn;
}
