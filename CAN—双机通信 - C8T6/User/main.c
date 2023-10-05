#include "stm32f10x.h"
#include "./usart/bsp_debug_usart.h"
#include "./led/bsp_led.h"   
#include "./key/bsp_key.h"  
#include "./can/bsp_can.h"
#include "Timer2.h"
#include "stepMotor.h"


__IO uint32_t flag = 0;		 //���ڱ�־�Ƿ���յ����ݣ����жϺ����и�ֵ	    
CanRxMsg RxMessage;				 //���ջ�����


void can_delay(__IO u32 nCount)
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
	
	Stepper_GPIOInit();
		
  /*��ʼ��USART1*/
  Debug_USART_Config();
 
	/*��ʼ��can,���жϽ���CAN���ݰ�*/
	CAN_Config();
	
	printf("\r\n��ʹ��CAN�������ݰ���\r\n"); 			
	printf("\r\n���͵ı�������Ϊ��\r\n");
	
  while(1)
	{
		
		if(flag == 1)
		{		
			printf("״̬%d��ת\r\n",flag);	
			flag=0;
			
			Stepper_RotateByLoop(Forward, 1, 3);
		}
		
		if(flag == 2)
		{		
			printf("״̬%d��ת\r\n",flag);
			flag=0;
			
			Stepper_RotateByLoop(Reversal, 1, 3);
		}

	}
	
 }


