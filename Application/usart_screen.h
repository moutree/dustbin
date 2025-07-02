#ifndef USART_SCREEN_H
#define USART_SCREEN_H

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "usart.h"
#include "bsp_usb.h"

void clear_lcd();
void LCD_task(void *arg);
void page_change(int page);
void transmit(uint8_t rbsclass);

#endif


