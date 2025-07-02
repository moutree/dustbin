#ifndef __COMPRESS_H
#define __COMPRESS_H

#include "bsp_can.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "Emm_V5.h"

void compress_task(void *arg);

void compress_ctrl();

#endif