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
//		usart_printf("page 分类界面\xff\xff\xff");//垃圾分类
		osDelay(200);
	}
}


uint8_t tras_flag = 0;

void page_change(int page)
{
	if(page==0)
	{
		usart_printf("page 宣传视屏界面\xff\xff\xff");//视频播放
		page=0;
		tras_flag = 0; 
	}
	 if(page==1)
	 {
		 usart_printf("page 分类界面\xff\xff\xff");//垃圾分类
		 page=1;
		 tras_flag = 1;
	 }
	 if(page==2)
	 {
		 usart_printf("page 可回收满载\xff\xff\xff");//可回收垃圾满载
		 page=2;
		 tras_flag = 0;
	 }
	 if(page==3)
	 {
		 usart_printf("page 厨余满载\xff\xff\xff");//厨余垃圾满载
		 page=3;
		 tras_flag = 0;
	 }
	 if(page==4)
	 {
		 usart_printf("page 有害满载\xff\xff\xff");//有害垃圾满载
		 page=4;
		 tras_flag = 0;
	 }
	 if(page==5)
	 {
		 usart_printf("page 建筑满载\xff\xff\xff");//建筑垃圾满载
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
			page_change(2);//可回收垃圾
		break;
		case 3:
			page_change(3);//厨余垃圾
		break;
		case 4:
			page_change(4);//有害垃圾
		break;
		case 5:
			page_change(5);//建筑垃圾
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
					usart_printf("data0.insert(\"%d^可回收垃圾^%d\")\xff\xff\xff",Senumber,rc_num);
					usart_printf("t0.txt=\"可回收垃圾分类成功！\"\xff\xff\xff");
					break;
				case '2':		
					Senumber++;
					kc_num++;
					usart_printf("data0.insert(\"%d^厨余垃圾垃圾^%d\")\xff\xff\xff",Senumber,kc_num);
					usart_printf("t0.txt=\"厨余垃圾分类成功！\"\xff\xff\xff");			
					break; 
				case '3':
					Senumber++;
					hf_num++;
					usart_printf("data0.insert(\"%d^有害垃圾垃圾^%d\")\xff\xff\xff",Senumber,hf_num);
					usart_printf("t0.txt=\"有害垃圾分类成功！\"\xff\xff\xff");			
				    break;
				case '4':
					Senumber++;
					bd_num++;
					usart_printf("data0.insert(\"%d^建筑垃圾垃圾^%d\")\xff\xff\xff",Senumber,bd_num);
					usart_printf("t0.txt=\"建筑垃圾分类成功！\"\xff\xff\xff");			
					break;
			}
			
	}
}

uint16_t cval = 0;

void clear_lcd()
{
		usart_printf("data0.clear()\xff\xff\xff");
}


