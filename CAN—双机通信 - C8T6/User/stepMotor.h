#ifndef __STEPMOTOR_H
#define __STEPMOTOR_H

#include <stdint.h>

// �������ת����
typedef enum 
{
	Forward = 0,
	Reversal = 1
} RotDirection;

// ��Ҫʹ�������˿�ʱ��ֻ��Ҫ�������µĺ궨�弴��
// ������Ҫ��֤�ĸ�����˿�ͬ��һ��GPIO
// �������������һ�㣬��Ҫ����Stepper.c�г�ʼ������Stepper_Init��Stepper_RotateByStep�е�һЩ��������
// ����ĺ궨����Ϊ����߳���Ŀɶ��ԺͿ���ֲ�ԣ���ʹ��stm32f10x.h�ж����ԭʼ����Ҳδ������
#define		Stepper_CLK				RCC_APB2Periph_GPIOB
#define		Stepper_Output_GPIO		GPIOB
#define 	Stepper_LA				GPIO_Pin_0
#define 	Stepper_LB				GPIO_Pin_1
#define 	Stepper_LC				GPIO_Pin_10
#define 	Stepper_LD				GPIO_Pin_11

void Stepper_GPIOInit(void);
void Stepper_Stop(void);
void Stepper_SingleStep(uint8_t StepNum, uint16_t Delay_Time_xms);
void Stepper_RotateByStep(RotDirection direction, uint32_t step, uint16_t Delay_Time_xms);
void Stepper_RotateByLoop(RotDirection direction, uint32_t Loop, uint16_t Delay_Time_xms);

#endif
