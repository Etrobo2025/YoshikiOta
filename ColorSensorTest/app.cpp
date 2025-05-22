#include "app.h"
#include <stdio.h>

#include "ColorSensor.h"
#include "Clock.h"

using namespace spikeapi;

// メインタスク
void main_task(intptr_t unused) {

    ColorSensor colorSensor(EPort::PORT_1); // カラーセンサをポート1に接続
    Clock clock; // クロックオブジェクト（タイミング用）

    while (1) {
        // カラーセンサのRGB値を取得
        int red = colorSensor.getRed();   // 赤の値
        int green = colorSensor.getGreen(); // 緑の値
        int blue = colorSensor.getBlue();  // 青の値

        // RGBの値を表示
        printf("カラーセンサの値 - 赤: %d, 緑: %d, 青: %d\n", red, green, blue);

        // 1秒待機
        clock.sleep(1000);  // 1000ミリ秒（1秒）待機
    }

    ext_tsk(); // タスク終了
}
