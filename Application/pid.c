#include "pid.h"
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : pid.c
  * @brief          : 分拣电机和传送带电机的PID配置
  ******************************************************************************
  * @attention
  *
  * 调节分拣电机的PID系数使用gimbal_PID_init()
	* 调节传送带电机的PID系数使用belt_PID_init()
	* 当前的装配顺序 belt_2 第一层 belt_3 第二层 belt_1 第三层
	
  ******************************************************************************
  */
pid_struct_t gimbal_yaw_speed_pid;
pid_struct_t gimbal_yaw_angle_pid;
pid_struct_t belt1_speed_pid; 
pid_struct_t belt2_speed_pid; 
pid_struct_t belt3_speed_pid; 
void pid_init(pid_struct_t *pid,
              float kp,
              float ki,
              float kd,
              float i_max,
              float out_max)
{
  pid->kp      = kp;
  pid->ki      = ki;
  pid->kd      = kd;
  pid->i_max   = i_max;
  pid->out_max = out_max;
}
 
 
float pid_calc(pid_struct_t *pid, float ref, float fdb)
{
  pid->ref = ref;
  pid->fdb = fdb;
  pid->err[1] = pid->err[0];
  pid->err[0] = pid->ref - pid->fdb;
  
  pid->p_out  = pid->kp * pid->err[0];
  pid->i_out += pid->ki * pid->err[0];
  pid->d_out  = pid->kd * (pid->err[0] - pid->err[1]);
  if(pid->i_out>=pid->i_max)
	  pid->i_out = pid->i_max;
  else if(pid->i_out<=-pid->i_max)
	  pid->i_out = -pid->i_max;
  
  pid->output = pid->p_out + pid->i_out + pid->d_out;
  if(pid->output>=pid->out_max)
	  pid->output = pid->out_max;
  else if(pid->output<=-pid->out_max)
	  pid->output = -pid->out_max;
  return pid->output;
}

 
float pid_gimbal_calc(pid_struct_t *pid, float ref, float fdb)
{
  pid->ref = ref;
  pid->fdb = fdb;
  pid->err[1] = pid->err[0];
  pid->err[0] = pid->ref - pid->fdb;
  
	if (pid->err[0]>4095)
		pid->err[0]-=8192;
	if (pid->err[0]<-4095)
		pid->err[0]+=8192;
  pid->p_out  = pid->kp * pid->err[0];
  pid->i_out += pid->ki * pid->err[0];
  pid->d_out  = pid->kd * (pid->err[0] - pid->err[1]);
  if(pid->i_out>=pid->i_max)
	  pid->i_out = pid->i_max;
  else if(pid->i_out<=-pid->i_max)
	  pid->i_out = -pid->i_max;
  
  pid->output = pid->p_out + pid->i_out + pid->d_out;
  if(pid->output>=pid->out_max)
	  pid->output = pid->out_max;
  else if(pid->output<=-pid->out_max)
	  pid->output = -pid->out_max;
  return pid->output;
}
 
void gimbal_PID_init()
{
//	pid_init(&gimbal_yaw_speed_pid, 80.0,5, 100, 30000, 20000);//P=30,I=0,D=0
//	pid_init(&gimbal_yaw_angle_pid, 100, 0.0, 800, 0, 16000);//P=400,I=0,D=0
	pid_init(&gimbal_yaw_speed_pid, 5.48, 0, 0, 30000, 30000);
	pid_init(&gimbal_yaw_angle_pid, 0.95, 0,0, 0, 320);
}

void belt_PID_init()
{
	pid_init(&belt1_speed_pid,1.5, 0.01, 0, 0, 2000);
	pid_init(&belt2_speed_pid,1.5, 0.01, 0, 0, 2000);
	pid_init(&belt3_speed_pid,1.5, 0.01, 0, 0, 2000);
}
