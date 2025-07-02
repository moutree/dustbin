#include "sort_motor.h"
#include "usart.h"
#define pi 3.1415926535


extern int flag;
extern moto_info_t motor_yaw_info;
extern pid_struct_t gimbal_yaw_speed_pid;
extern pid_struct_t gimbal_yaw_angle_pid;
extern type_struct_t type_struct;
float PC_data;


void sort_task(void *arg)
{
	type_init(&type_struct);
	while(1)
	{
		type_judge(&type_struct,UserRxBufferFS[0]);
		sort_ctrl();
		osDelay(2);
	}
}


void sort_ctrl()
{	
//	  // 发送数据
//    uint8_t message[] = "yes!\r\n";//发送字符
//    CDC_Transmit_FS(message, sizeof(message) - 1);
//		int num1 = 123, num2 = 456, num3 = 789;//发送数字
//		char num_message[100];  // 用来存放多个数字的字符串
//    // 格式化多个整数为一个字符串
//    sprintf(num_message, "num1: %d, num2: %d, num3: %d\r\n", num1, num2, num3);
//    CDC_Transmit_FS(num_message, sizeof(num_message) - 1);
    switch(1)
		{
			case '1':
		pid_gimbal_calc(&gimbal_yaw_angle_pid,154, motor_yaw_info.rotor_angle);break;
			case '2':
		pid_gimbal_calc(&gimbal_yaw_angle_pid,2525, motor_yaw_info.rotor_angle);break;
			case '3':
		pid_gimbal_calc(&gimbal_yaw_angle_pid,4250, motor_yaw_info.rotor_angle);break;
			case '4':
		pid_gimbal_calc(&gimbal_yaw_angle_pid,7987, motor_yaw_info.rotor_angle);break;
			default:
		if(flag == 0)
		pid_gimbal_calc(&gimbal_yaw_angle_pid,5400, motor_yaw_info.rotor_angle);break;		
		}
		if(flag == 0)
		pid_gimbal_calc(&gimbal_yaw_angle_pid,5400, motor_yaw_info.rotor_angle);
		pid_calc(&gimbal_yaw_speed_pid,gimbal_yaw_angle_pid.output, motor_yaw_info.rotor_speed);
		set_GM6020_motor_voltage(&hcan1,gimbal_yaw_speed_pid.output);
		
//		osDelay(2000);
//	motor_flag = 1;
//		    if(1)
//		{
//        osDelay(2000);
//		if(1)
//		    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 500);
//        osDelay(2000);
//        __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 1500);
//	
//     }
}