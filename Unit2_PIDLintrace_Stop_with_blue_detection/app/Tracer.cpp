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
        printf("障害物検知を検知したため、回避走行を行います。\n");
        int mpower = 50;
        const uint32_t duration = 1000000;
        while(1){
           

            leftWheel.stop();
            rightWheel.stop();
            clock.sleep(1000000);
            
            leftWheel.setPower(-mpower);
            rightWheel.setPower(-mpower);
            clock.sleep(200000);
            
            leftWheel.setPower(mpower);
            rightWheel.setPower(-mpower);
            clock.sleep(1000000);
            
            leftWheel.setPower(mpower);
            rightWheel.setPower(mpower);
            clock.sleep(700000);
            
            leftWheel.setPower(-mpower);
            rightWheel.setPower(mpower);
            clock.sleep(1000000);
            
            leftWheel.setPower(mpower);
            rightWheel.setPower(mpower);
            clock.sleep(2000000);
          
            leftWheel.setPower(-mpower);
            rightWheel.setPower(mpower);
            clock.sleep(600000);
            
            leftWheel.setPower(35);
            rightWheel.setPower(35);
            clock.sleep(1000000);
            
           while(true){ 
              ColorSensor::RGB rgb;
              colorSensor.getRGB(rgb);

            int r = rgb.r;
            int g = rgb.g;
            int b = rgb.b;
            
            int total = r + g + b;
            
             
            if (total < 500) {
                printf("黒を検知したためライトレースに復帰します。%d\n,total");
                  leftWheel.stop();
                  rightWheel.stop();
                  clock.sleep(1000000);
                  
                  printf("角度修正。\n");
                  leftWheel.setPower(mpower);
                  rightWheel.setPower(-mpower);
                  clock.sleep(400000);

                  return;
          }
        }
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
    printf("青色を検知：ダブルループに突入します。\n");
    int flag = 0;
    
    if(traceflag==1){
       flag=3;
      }else {
     flag=0;
  }
    int mpower=50;
    
    switch(flag){
      case 0: {
        while(1){
                printf("case0を実行します。\n");
                
                leftWheel.stop();
                rightWheel.stop();
                clock.sleep(1000000);
                
                leftWheel.setPower(-mpower);
                rightWheel.setPower(mpower);
                clock.sleep(200000);
                flag = 1;
                printf("case0を終了します。\n");
                break;
              }
            }
                
       case 1:{
       while(1){
                printf("case1を実行します。\n");
                leftWheel.setPower(40);
                rightWheel.setPower(40);
                clock.sleep(3000000);
                printf("case1を終了します。\n");
                flag=2;
                break;
              }
            }
              
       case 2:{
       while(1){
              ColorSensor::RGB rgb;
              colorSensor.getRGB(rgb);

              int r = rgb.r;
              int g = rgb.g;
              int b = rgb.b;
            
              int total = r + g + b;
         
              printf("case2を実行します。\n");
         
              if (total < 500) {
                printf("黒を検知しました。\n");
                
                leftWheel.stop();
                rightWheel.stop();
                clock.sleep(1000000);
                
                leftWheel.stop();
                rightWheel.setPower(mpower);
                clock.sleep(850000);
                traceflag=1;
                printf("case2を終了します。\n");
        
                break;
              }
            }
          }
          break;
          
              
       case 3:{
                while(1){
                  printf("case3を実行します。\n");
                  leftWheel.stop();
                  rightWheel.stop();
                  clock.sleep(1000000);
                    leftWheel.setPower(mpower);
                rightWheel.setPower(mpower);
                clock.sleep(500000);
                
                  flag=4;
                  break;
                }
              }
              
       case 4:{
              while(1){
         
                printf("case4を実行します。\n");
                
                ColorSensor::RGB rgb;
                colorSensor.getRGB(rgb);

                int r = rgb.r;
                int g = rgb.g;
                int b = rgb.b;
            
                int total = r + g + b;
         
              if (total < 500) {
                printf("黒を検知しました。\n");
                while(1){
                    leftWheel.stop();
                    rightWheel.stop();
                    clock.sleep(1000000);
                    flag=5;
                    printf("case4を終了します。\n");
                    break;
                  }
                }
                break;
         }       
      }
      
    case 5: {
      while(1){
        printf("case5を実行します。");
                leftWheel.setPower(mpower);
                rightWheel.setPower(-mpower);
                clock.sleep(800000);
                break;
        }
      }
      
      
        
        }
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
  
  if(traceflag==1){
  return -turn;
} else {
  return turn;
}
}
