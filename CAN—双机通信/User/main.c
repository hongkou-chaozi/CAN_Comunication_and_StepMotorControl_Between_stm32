#include "stm32f10x.h"
#include "./usart/bsp_debug_usart.h"
#include "./led/bsp_led.h"   
#include "./key/bsp_key.h"  
#include "./can/bsp_can.h"


__IO uint32_t flag = 0;		 //用于标志是否接收到数据，在中断函数中赋值
CanTxMsg TxMessage;			     //发送缓冲区
CanRxMsg RxMessage;				 //接收缓冲区


/// 不精确的延时
static void can_delay(__IO u32 nCount)
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
	LED_GPIO_Config();
	
  /*初始化USART1*/
  Debug_USART_Config();
	
	/*初始化按键*/
	Key_GPIO_Config();
 
	/*初始化can,在中断接收CAN数据包*/
	CAN_Config();

  while(1)
	{
		/*按一次按键发送一次数据*/
		if(	Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON)
		{

			/*设置要发送的报文*/
			CAN_SetMsg_KEY1(&TxMessage);
			/*把报文存储到发送邮箱，发送*/
			CAN_Transmit(CANx, &TxMessage);
			
			can_delay(1000);
			
			LED_GREEN;
			
			printf("\r\n已使用CAN发送数据包！\r\n"); 			
			printf("\r\n发送的报文内容为：\r\n");
			printf("\r\n 扩展ID号ExtId：0x%x \r\n",TxMessage.ExtId);
			CAN_DEBUG_ARRAY(TxMessage.Data,1); 

		}
		
				/*按一次按键发送一次数据*/
		if(	Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON)
		{

			/*设置要发送的报文*/
			CAN_SetMsg_KEY2(&TxMessage);
			/*把报文存储到发送邮箱，发送*/
			CAN_Transmit(CANx, &TxMessage);
			
			can_delay(1000);
			
			LED_GREEN;
			
			printf("\r\n已使用CAN发送数据包！\r\n"); 			
			printf("\r\n发送的报文内容为：\r\n");
			printf("\r\n 扩展ID号ExtId：0x%x \r\n",TxMessage.ExtId);
			CAN_DEBUG_ARRAY(TxMessage.Data,1); 

		}
	}
}

