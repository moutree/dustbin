#ifndef BELT_MOTOR_H
#define BELT_MOTOR_H


#include "pid.h"
#include "type.h"
#include "bsp_can.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "usbd_cdc_if.h"
void belt_task(void *arg);
void belt_ctrl();

extern int onething_going_flag;

#endif