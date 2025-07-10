#include "Motor.h"
#include "ColorSensor.h"
#include "UltrasonicSensor.h" 

using namespace spikeapi;

class Tracer {
public:
  Tracer();
  void run();
  void init();
  void terminate();

private:
  float calc_pid_value();
  Motor leftWheel;
  Motor rightWheel;
  ColorSensor colorSensor;
  UltrasonicSensor ultrasonic;
  const int8_t mThreshold = 20;
  float integral=0.0f;
  float previousError=0.0f;
#ifndef MAKE_RASPIKE
  const int8_t pwm = 50;
#else
  const int8_t pwm = 50;
#endif
  float calc_prop_value();
};
