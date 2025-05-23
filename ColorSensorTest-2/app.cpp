//app.cpp

#include "app.h"
#include <stdio.h>

#include "ColorSensor.h"
#include "ForceSensor.h"
#include "Clock.h"

using namespace spikeapi;

ColorSensor clorSensor(EPort::PORT_E); //カラーセンサをポートをEに接続
ForceSensor forceSensor(EPort::PORT_D); //フォースセンサをポートDに指定
Clock clock;

void main_task(inptr_t unused){
    rgb_raw_t rgb; //RGB値格納構造体
    const unit32_t interval =  1000 * 1000; //1000ms
    printf("RGB Logger Start\n");

    while(!forceSensor.isTouched()){
        colorSensor.getRawColor(rgb); //RGB値取得

        printf("R: %d,G: %d,B: %d\n",rgb.r,rgb.g,rgb.b);

        clock.sleep(interval);
    }

    printf("RGB Logger Stooped\n");
    ext_tsk(); //タスク終了
}
