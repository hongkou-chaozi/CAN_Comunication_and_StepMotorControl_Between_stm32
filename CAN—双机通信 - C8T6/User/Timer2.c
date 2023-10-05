#include "Timer2.h"
#include "stm32f10x.h"

uint16_t CCR_Val;
TIM_OCInitTypeDef  TIM_OCInitStructure;

void TIM2_GPIO_Config() 
{
	GPIO_InitTypeDef GPIO_InitStructure;

  // ����Ƚ�ͨ��2 GPIO ��ʼ��  PA1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void TIM2_Mode_Config()
{
	// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

/*--------------------ʱ���ṹ���ʼ��-------------------------*/
	// �������ڣ���������Ϊ100K
	
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Period = 2000 -1;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler = 7200 - 1;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;	
	// ��ʼ����ʱ��
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	/*--------------------����ȽϽṹ���ʼ��-------------------*/	
	// ռ�ձ�����
	uint16_t CCR_Val = 0;
	
	// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// ����Ƚ�ͨ�� 2
	TIM_OCInitStructure.TIM_Pulse = CCR_Val;
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	// ʹ�ܼ�����
	TIM_Cmd(TIM2, ENABLE);
}

void TIM2_Init()
{
	TIM2_GPIO_Config();
	TIM2_Mode_Config();
}

