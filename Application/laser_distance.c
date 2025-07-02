#include "laser_distance.h"
#include "usart.h"


uint16_t distance = 0;       // �洢���յ���distance����
char ReceiveBuff[50];        // �������ݵĻ�����extern uint16_t distance;



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
	 // �Ӵ���6��������
        HAL_UART_Receive(&huart6, (uint8_t *)ReceiveBuff, sizeof(ReceiveBuff), HAL_MAX_DELAY);

        // �����յ����ַ���ת��Ϊ uint16_t ���͵� distance
//        distance = (uint16_t)atoi(ReceiveBuff);  // ʹ�� atoi ���ַ���ת��Ϊ�޷�������
//				sscanf(ReceiveBuff, "%hu", &distance);
char *valid_data = ReceiveBuff;
while (*valid_data == '\0') {
    valid_data++;  // �������� 0x00
}
distance = (uint16_t)atoi(valid_data);

}

			 