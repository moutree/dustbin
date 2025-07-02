#include "type.h"
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : type.c
  * @brief          : 垃圾分类
  ******************************************************************************
  * @attention
  *
  * 已舍弃，并未采用该.c文件
	
  ******************************************************************************
  */
type_struct_t type_struct;

void type_init(type_struct_t *Type)
{
	Type->type = 4;
	Type->last_type = 4;
	Type->last_2_type = 4;
}
int type_judge(type_struct_t *Type,uint8_t PC_data)
{
	Type->type = PC_data;
	Type->last_type = Type->type;
	Type->last_2_type = Type->last_type;
	if ((Type->type == Type->last_type)&&(Type->type == Type->last_2_type))
	{
		Type->final_type = Type->type;
	}
	else
	{
		Type->final_type =4; 
	}
	return Type->final_type;
}

void type_reset(type_struct_t *Type)
{
	Type->type = 4;
	Type->last_type = 4;
	Type->last_2_type = 4;
}