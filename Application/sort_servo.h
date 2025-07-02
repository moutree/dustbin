#ifndef SORT_SERVO_H
#define SORT_SERVO_H

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "tim.h"
#include "usbd_cdc_if.h"
void servo_task(void *arg);
void servo_ctrl();

#endif