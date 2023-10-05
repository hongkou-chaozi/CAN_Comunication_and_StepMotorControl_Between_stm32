#include "stm32f10x.h"
#include "./usart/bsp_debug_usart.h"
#include "./led/bsp_led.h"   
#include "./key/bsp_key.h"  
#include "./can/bsp_can.h"


__IO uint32_t flag = 0;		 //���ڱ�־�Ƿ���յ����ݣ����жϺ����и�ֵ
CanTxMsg TxMessage;			     //���ͻ�����
CanRxMsg RxMessage;				 //���ջ�����


/// ����ȷ����ʱ
static void can_delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	LED_GPIO_Config();
	
  /*��ʼ��USART1*/
  Debug_USART_Config();
	
	/*��ʼ������*/
	Key_GPIO_Config();
 
	/*��ʼ��can,���жϽ���CAN���ݰ�*/
	CAN_Config();

  while(1)
	{
		/*��һ�ΰ�������һ������*/
		if(	Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON)
		{

			/*����Ҫ���͵ı���*/
			CAN_SetMsg_KEY1(&TxMessage);
			/*�ѱ��Ĵ洢���������䣬����*/
			CAN_Transmit(CANx, &TxMessage);
			
			can_delay(1000);
			
			LED_GREEN;
			
			printf("\r\n��ʹ��CAN�������ݰ���\r\n"); 			
			printf("\r\n���͵ı�������Ϊ��\r\n");
			printf("\r\n ��չID��ExtId��0x%x \r\n",TxMessage.ExtId);
			CAN_DEBUG_ARRAY(TxMessage.Data,1); 

		}
		
				/*��һ�ΰ�������һ������*/
		if(	Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON)
		{

			/*����Ҫ���͵ı���*/
			CAN_SetMsg_KEY2(&TxMessage);
			/*�ѱ��Ĵ洢���������䣬����*/
			CAN_Transmit(CANx, &TxMessage);
			
			can_delay(1000);
			
			LED_GREEN;
			
			printf("\r\n��ʹ��CAN�������ݰ���\r\n"); 			
			printf("\r\n���͵ı�������Ϊ��\r\n");
			printf("\r\n ��չID��ExtId��0x%x \r\n",TxMessage.ExtId);
			CAN_DEBUG_ARRAY(TxMessage.Data,1); 

		}
	}
}

