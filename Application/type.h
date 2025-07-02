#ifndef __TYPE_H_
#define __TYPE_H_
 
#include "main.h"
#include "stm32f4xx.h"
 
typedef struct _type_struct_t
{
	int type; //当次种类
	int last_type; //上次种类
	int last_2_type; // 上上次种类
	int final_type; //最终判定
  
}type_struct_t;
 
void type_init(type_struct_t *Type);
int type_judge(type_struct_t *Type,uint8_t PC_data);
void type_reset(type_struct_t *Type);
							
#endif