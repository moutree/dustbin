#ifndef __PID_H_
#define __PID_H_
 
#include "main.h"
#include "stm32f4xx.h"
 
typedef struct _pid_struct_t
{
  float kp;//??
  float ki;//??
  float kd;//??
  float i_max;//????
  float out_max;//????
  
  float ref;      // target value????
  float fdb;      // feedback value????
  float err[2];   // error and last error??
 
  float p_out;//????
  float i_out;//????
  float d_out;//????
  float output;//pid???
}pid_struct_t;
 
void pid_init(pid_struct_t *pid,
              float kp,
              float ki,
              float kd,
              float i_max,
              float out_max);
 
void gimbal_PID_init(void);
void belt_PID_init();
float pid_calc(pid_struct_t *pid, float ref, float fdb);
float pid_gimbal_calc(pid_struct_t *pid, float ref, float fdb);
							
#endif