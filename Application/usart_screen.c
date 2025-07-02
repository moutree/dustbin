#include "usart_screen.h"
#include "usbd_cdc_if.h"

uint8_t Senbuff[100];

uint16_t first_join_flag = 0;

uint8_t rbsclass = 0;
uint16_t Senumber = 0;
uint16_t rc_num = 0;
uint16_t kc_num = 0;
uint16_t hf_num = 0;
uint16_t bd_num = 0;
uint8_t BUF;


void LCD_task(void *arg)
{

	while(1)
	{	
			if(UserRxBufferFS[0] == '1'||UserRxBufferFS[0] == '2'||UserRxBufferFS[0] == '3'||UserRxBufferFS[0] == '4')
			{
				if(first_join_flag == 0)
				{
					page_change(0);
					clear_lcd();
					first_join_flag = 1;
				}
			}
//	    BUF = UserRxBufferFS[0];
//		transmit(BUF);
//		usart_printf("page �������\xff\xff\xff");//��������
		osDelay(200);
	}
}


uint8_t tras_flag = 0;

void page_change(int page)
{
	if(page==0)
	{
		usart_printf("page ������������\xff\xff\xff");//��Ƶ����
		page=0;
		tras_flag = 0; 
	}
	 if(page==1)
	 {
		 usart_printf("page �������\xff\xff\xff");//��������
		 page=1;
		 tras_flag = 1;
	 }
	 if(page==2)
	 {
		 usart_printf("page �ɻ�������\xff\xff\xff");//�ɻ�����������
		 page=2;
		 tras_flag = 0;
	 }
	 if(page==3)
	 {
		 usart_printf("page ��������\xff\xff\xff");//������������
		 page=3;
		 tras_flag = 0;
	 }
	 if(page==4)
	 {
		 usart_printf("page �к�����\xff\xff\xff");//�к���������
		 page=4;
		 tras_flag = 0;
	 }
	 if(page==5)
	 {
		 usart_printf("page ��������\xff\xff\xff");//������������
		 page=5;
		 tras_flag = 0;
	 }
}

uint16_t warning;

void Full_Warm(warning)
{
	switch(warning)
	{
		case 2:
			page_change(2);//�ɻ�������
		break;
		case 3:
			page_change(3);//��������
		break;
		case 4:
			page_change(4);//�к�����
		break;
		case 5:
			page_change(5);//��������
		break;
	}	
}



void transmit(uint8_t rbsclass)
{
	if(tras_flag == 1)
	{
		switch(rbsclass)
			{
				case '1':		
					Senumber++;
					rc_num++;
					usart_printf("data0.insert(\"%d^�ɻ�������^%d\")\xff\xff\xff",Senumber,rc_num);
					usart_printf("t0.txt=\"�ɻ�����������ɹ���\"\xff\xff\xff");
					break;
				case '2':		
					Senumber++;
					kc_num++;
					usart_printf("data0.insert(\"%d^������������^%d\")\xff\xff\xff",Senumber,kc_num);
					usart_printf("t0.txt=\"������������ɹ���\"\xff\xff\xff");			
					break; 
				case '3':
					Senumber++;
					hf_num++;
					usart_printf("data0.insert(\"%d^�к���������^%d\")\xff\xff\xff",Senumber,hf_num);
					usart_printf("t0.txt=\"�к���������ɹ���\"\xff\xff\xff");			
				    break;
				case '4':
					Senumber++;
					bd_num++;
					usart_printf("data0.insert(\"%d^������������^%d\")\xff\xff\xff",Senumber,bd_num);
					usart_printf("t0.txt=\"������������ɹ���\"\xff\xff\xff");			
					break;
			}
			
	}
}

uint16_t cval = 0;

void clear_lcd()
{
		usart_printf("data0.clear()\xff\xff\xff");
}


