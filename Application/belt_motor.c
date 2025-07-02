#include "belt_motor.h"

#include "usbd_cdc_if.h"

int open;
extern moto_info_t motor1_belt_info;
extern moto_info_t motor2_belt_info;
extern moto_info_t motor3_belt_info;
extern pid_struct_t belt1_speed_pid;
extern pid_struct_t belt2_speed_pid;
extern pid_struct_t belt3_speed_pid;
extern uint16_t distance;
int onething_flag;
int onething_going_flag = 0;
int first_nothing_flag;
void belt_task(void *arg)
{
	while(1)
	{
		belt_ctrl();
		osDelay(2);
	}
}



void belt_ctrl()
{
	
	if(UserRxBufferFS[0]=='5')
	{
		open=1;
	}
//		if(distance <110)
//		{
//			onething_going_flag = 1;
//			onething_flag = 0;
//							    pid_calc(&belt3_speed_pid,1150, motor3_belt_info.rotor_speed);
//		            pid_calc(&belt2_speed_pid,1150, motor2_belt_info.rotor_speed);
//		}
//		else if(distance >110&&onething_going_flag==0)
//		{
//										    pid_calc(&belt3_speed_pid,1150, motor3_belt_info.rotor_speed);
//		            pid_calc(&belt2_speed_pid,1150, motor2_belt_info.rotor_speed);
//		}
//		else if(distance >110 && onething_going_flag==1)
//		{
//			onething_flag = 1;
//			onething_going_flag=0;
//			 pid_calc(&belt3_speed_pid,1150, motor3_belt_info.rotor_speed);
//		            pid_calc(&belt2_speed_pid,1150, motor2_belt_info.rotor_speed);
//		}
//		else if(onething_flag == 1)
//		{
//			 pid_calc(&belt3_speed_pid,0, motor3_belt_info.rotor_speed);
//		    pid_calc(&belt2_speed_pid,0, motor2_belt_info.rotor_speed);
////			osDelay(2);
//		}
//		else
//		{
//				    pid_calc(&belt3_speed_pid,1150, motor3_belt_info.rotor_speed);
//		            pid_calc(&belt2_speed_pid,1150, motor2_belt_info.rotor_speed);
////	      if(onething_flag == 2)
////		  {
////			   pid_calc(&belt3_speed_pid,1150, motor3_belt_info.rotor_speed);
////		   pid_calc(&belt2_speed_pid,1150, motor2_belt_info.rotor_speed);
////		  }
//		}
//	if(distance>120)
//{
//	first_nothing_flag =1;
//	 pid_calc(&belt3_speed_pid,1150, motor3_belt_info.rotor_speed);
//    pid_calc(&belt2_speed_pid,1150, motor2_belt_info.rotor_speed);
//    if(distance<120)
//	{
//		onething_going_flag = 1;
//	}
//	if(distance>120 && onething_going_flag == 1)
//	{
//		pid_calc(&belt3_speed_pid,0, motor3_belt_info.rotor_speed);
//    pid_calc(&belt2_speed_pid,0, motor2_belt_info.rotor_speed);
//		onething_flag = 1;
//	}
//}
//belt_2 第一层 belt_3 第二层 belt_1 第三层
//	if(distance > 120 && onething_going_flag != 1)
//	{
//		pid_calc(&belt1_speed_pid,1150*3/2, motor1_belt_info.rotor_speed);
//		pid_calc(&belt3_speed_pid,1150/3*2, motor3_belt_info.rotor_speed);
//		pid_calc(&belt2_speed_pid,1150/2, motor2_belt_info.rotor_speed);
//		CAN_cmd_3508(belt1_speed_pid.output,belt2_speed_pid.output,belt3_speed_pid.output,belt3_speed_pid.output);
//	}
//	else if(distance < 120 && distance != 0 && onething_going_flag != 1)
//	{
//		onething_going_flag = 1;
//		pid_calc(&belt1_speed_pid,1150*3/2, motor1_belt_info.rotor_speed);
//		pid_calc(&belt3_speed_pid,1150/3*2, motor3_belt_info.rotor_speed);
//		pid_calc(&belt2_speed_pid,1150/2, motor2_belt_info.rotor_speed);
//		CAN_cmd_3508(belt1_speed_pid.output,belt2_speed_pid.output,belt3_speed_pid.output,belt3_speed_pid.output);
//	}
//	
//	else if(distance > 120 && onething_going_flag == 1)
//	{
//		pid_calc(&belt3_speed_pid,0, motor3_belt_info.rotor_speed);
//		pid_calc(&belt2_speed_pid,0, motor2_belt_info.rotor_speed);
//		pid_calc(&belt1_speed_pid,1150*2, motor1_belt_info.rotor_speed);
//		CAN_cmd_3508(belt1_speed_pid.output,belt2_speed_pid.output,belt3_speed_pid.output,belt3_speed_pid.output);
//	}
	
/****************激光传感器在第三层的控制逻辑************************************/	
//belt_2 第一层 belt_3 第二层 belt_1 第三层
if(1)
{
	if(distance > 100 && onething_going_flag != 1)
	{
//		pid_calc(&belt1_speed_pid,1150*3/2, motor1_belt_info.rotor_speed);//3
		pid_calc(&belt1_speed_pid,1150*3/2, motor1_belt_info.rotor_speed);//3
		pid_calc(&belt3_speed_pid,1150/3*2, motor3_belt_info.rotor_speed);//2
		pid_calc(&belt2_speed_pid,1400, motor2_belt_info.rotor_speed);//1
		CAN_cmd_3508(belt1_speed_pid.output,belt2_speed_pid.output,belt3_speed_pid.output,belt3_speed_pid.output);
	}
	else if(distance < 100 && distance != 0 && onething_going_flag != 1)
	{
		onething_going_flag = 1;
//		pid_calc(&belt1_speed_pid,1150*3/2, motor1_belt_info.rotor_speed);
				pid_calc(&belt1_speed_pid,1150*3/2, motor1_belt_info.rotor_speed);//3
		pid_calc(&belt3_speed_pid,1150/3*2, motor3_belt_info.rotor_speed);
		pid_calc(&belt2_speed_pid,1400/2, motor2_belt_info.rotor_speed);
		CAN_cmd_3508(belt1_speed_pid.output,belt2_speed_pid.output,belt3_speed_pid.output,belt3_speed_pid.output);
	}
	
	else if(distance > 100 && onething_going_flag == 1)
	{
		pid_calc(&belt3_speed_pid,0, motor3_belt_info.rotor_speed);//2
		pid_calc(&belt2_speed_pid,0, motor2_belt_info.rotor_speed);//1
		pid_calc(&belt1_speed_pid,0, motor1_belt_info.rotor_speed);//3
		CAN_cmd_3508(belt1_speed_pid.output,belt2_speed_pid.output,belt3_speed_pid.output,belt3_speed_pid.output);
	}
/***************************************************************************/			
//	    pid_calc(&belt1_speed_pid,1150, motor1_belt_info.rotor_speed);
//		pid_calc(&belt2_speed_pid,1150, motor2_belt_info.rotor_speed);

//		pid_calc(&belt1_speed_pid,1150, motor1_belt_info.rotor_speed);
//		CAN_cmd_3508(belt1_speed_pid.output,belt2_speed_pid.output,belt3_speed_pid.output,belt3_speed_pid.output);
}	
}



