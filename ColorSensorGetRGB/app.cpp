#include "app.h"
#include <stdio.h>

#include "Clock.h" 
#include "ColorSensor.h"

using namespace spikeapi; 

 struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};
 
void main_task(intptr_t unused) { 

  ColorSensor colorSensor(EPort::PORT_E);
  Clock clock;
  ColorSensor::RGB rgb;

#ifndef MAKE_RASPIKE
  const int8_t pwm = 80;
#else
  const int8_t pwm = 80;
#endif

  const uint32_t duration = 1000*1000; 
  
  printf("カラーセンサーRGB取得開始\n");

  while(1) { 
    
    colorSensor.getRGB(rgb);
    printf("R:%d G:%d B:%d\n", rgb.r, rgb.g, rgb.b);
    clock.sleep(duration); 
    
  } 
  ext_tsk(); 
}
