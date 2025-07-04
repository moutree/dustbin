#include "compress.h"


// 定义实时位置全局变量
float pos = 0.0f, Motor_Cur_Pos = 0.0f;

void compress_task(void *arg)
{
	while(1)
	{
		compress_ctrl();
		osDelay(2);
	}
}


void compress_ctrl()
{
	/**********************************************************
***	位置模式：方向CW，速度1000RPM，加速度0（不使用加减速直接启动），脉冲数3200（16细分下发送3200个脉冲电机转一圈），相对运动
**********************************************************/	
  Emm_V5_Pos_Control(1, 1, 1000, 0, 2400, 0, 0);

/**********************************************************
	*	等待返回命令
***	返回数据缓存在can.rxData数组上，长度为can.CAN_RxMsg.DLC,
***	电机地址为帧ID右移8位：can.CAN_RxMsg.ExtId >> 8
**********************************************************/	
	while(can.rxFrameFlag == false);can.rxFrameFlag = false;


/**********************************************************
***	上电延时2秒等待Emm_V5.0闭环初始化完毕
**********************************************************/	
	HAL_Delay(2000);

/**********************************************************
***	位置模式：方向CW，速度1000RPM，加速度0（不使用加减速直接启动），脉冲数3200（16细分下发送3200个脉冲电机转一圈），相对运动
**********************************************************/	
  Emm_V5_Pos_Control(1, 0, 1000, 0, 2400, 0, 0);
/**********************************************************
	*	等待返回命令
***	返回数据缓存在can.rxData数组上，长度为can.CAN_RxMsg.DLC,
***	电机地址为帧ID右移8位：can.CAN_RxMsg.ExtId >> 8
**********************************************************/	
	while(can.rxFrameFlag == false); can.rxFrameFlag = false;
	
	
/**********************************************************
***	延时2秒，等待运动完成
**********************************************************/	
  HAL_Delay(2000);


/**********************************************************
***	读取电机实时位置
**********************************************************/	
  Emm_V5_Read_Sys_Params(1, S_CPOS);
	
	
/**********************************************************
	*	等待返回命令
***	返回数据缓存在can.rxData数组上，长度为can.CAN_RxMsg.DLC,
***	电机地址为帧ID右移8位：can.CAN_RxMsg.ExtId >> 8
**********************************************************/	
	while(can.rxFrameFlag == false);can.rxFrameFlag = false;


/**********************************************************
***	校验功能码、返回数据长度，校验成功则计算当前位置角度
**********************************************************/	
  if(can.rxData[0] == 0x36 && can.CAN_RxMsg.DLC == 7)
  {
    // 拼接成uint32_t类型
		pos = (uint32_t)(
											((uint32_t)can.rxData[2] << 24)		|
											((uint32_t)can.rxData[3] << 16)  	|
											((uint32_t)can.rxData[4] << 8)   	|
											((uint32_t)can.rxData[5] << 0)
										);

    // 转换成角度
    Motor_Cur_Pos = (float)pos * 360.0f / 65536.0f;

    // 符号
    if(can.rxData[1]) { Motor_Cur_Pos = -Motor_Cur_Pos; }
  }

  
	
}