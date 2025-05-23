#ifndef APP_H_
#define APP_H_

#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include <stdint.h>

#define MAIN_TASK 1  // タスクID定義を追加

extern void main_task(intptr_t exinf);

#endif
