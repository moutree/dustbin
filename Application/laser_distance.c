#include "laser_distance.h"
#include "usart.h"


uint16_t distance = 0;       // 存储接收到的distance数据
char ReceiveBuff[50];        // 接收数据的缓冲区extern uint16_t distance;



void laser_task(void *arg)
{

	while(1)
	{

		laser_distance_get();
		osDelay(2);
	}
}


void laser_distance_get()
{
	 // 从串口6接收数据
        HAL_UART_Receive(&huart6, (uint8_t *)ReceiveBuff, sizeof(ReceiveBuff), HAL_MAX_DELAY);

        // 将接收到的字符串转换为 uint16_t 类型的 distance
//        distance = (uint16_t)atoi(ReceiveBuff);  // 使用 atoi 将字符串转换为无符号整数
//				sscanf(ReceiveBuff, "%hu", &distance);
char *valid_data = ReceiveBuff;
while (*valid_data == '\0') {
    valid_data++;  // 跳过所有 0x00
}
distance = (uint16_t)atoi(valid_data);

}

			 