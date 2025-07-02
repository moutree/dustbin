#ifndef __BSP_CAN_H_
#define __BSP_CAN_H_
 
#include "main.h"
#include "can.h"
#include "stm32f4xx.h"
 
typedef struct
{
    uint16_t can_id;//??ID
    int16_t  set_voltage;//??????
    uint16_t rotor_angle;//????
    int16_t  rotor_speed;//??
    int16_t  torque_current;//????
    uint8_t  temp;//??
}moto_info_t;
 
void can_filter_init(void);
void set_GM6020_motor_voltage(CAN_HandleTypeDef* hcan,int16_t v1);
void CAN_cmd_reset_ID(void);
void CAN_cmd_3508(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4);
#endif