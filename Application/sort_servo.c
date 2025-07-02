#include "sort_servo.h"
#include "belt_motor.h"
#include "usart_screen.h"
int flag;
uint8_t buf;

void servo_task(void *arg)
{
  __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 2800);
	while(1)
	{	
		servo_ctrl();		
		osDelay(2);

	}
}
int a=1000;
void servo_ctrl()
{
	if((buf == '1')||(buf == '2')||(buf == '3')||(buf == '4'))
		{
		flag=1;
		
         
		}
	else
	{
		flag = 0;
	}
	if(flag)
	{
			osDelay(1500);	
		    transmit(buf);
	   		 __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 3500);
//		a = !a;
            osDelay(1000);
            __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 2800);
		    buf='0';
	         flag = 0;
			onething_going_flag = 0;
	}
}
