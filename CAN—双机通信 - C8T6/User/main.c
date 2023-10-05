#include "stm32f10x.h"
#include "./usart/bsp_debug_usart.h"
#include "./led/bsp_led.h"   
#include "./key/bsp_key.h"  
#include "./can/bsp_can.h"
#include "Timer2.h"
#include "stepMotor.h"


__IO uint32_t flag = 0;		 //用于标志是否接收到数据，在中断函数中赋值	    
CanRxMsg RxMessage;				 //接收缓冲区


void can_delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} 

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	
	Stepper_GPIOInit();
		
  /*初始化USART1*/
  Debug_USART_Config();
 
	/*初始化can,在中断接收CAN数据包*/
	CAN_Config();
	
	printf("\r\n已使用CAN发送数据包！\r\n"); 			
	printf("\r\n发送的报文内容为：\r\n");
	
  while(1)
	{
		
		if(flag == 1)
		{		
			printf("状态%d正转\r\n",flag);	
			flag=0;
			
			Stepper_RotateByLoop(Forward, 1, 3);
		}
		
		if(flag == 2)
		{		
			printf("状态%d反转\r\n",flag);
			flag=0;
			
			Stepper_RotateByLoop(Reversal, 1, 3);
		}

	}
	
 }


