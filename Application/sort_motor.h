#ifndef SORT_MOTOR_H
#define SORT_MOTOR_H


#include "pid.h"
#include "type.h"
#include "bsp_can.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "usbd_cdc_if.h"
void sort_task(void *arg);
void sort_ctrl();

#endif