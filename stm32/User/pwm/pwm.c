#include "pwm.h"
#include "stm32f10x.h"  



void pwm_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;   //������ʼ��GPIO�Ľṹ�����

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;//������ʼ����ʱ���Ľṹ�����

	TIM_OCInitTypeDef TIM_OCInitStructure;//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx

	//����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	//  ����GPIO��ģʽ��IO��
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;// PC6
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//�����������
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	//TIM3��ʱ����ʼ��
	TIM_TimeBaseInitStructure.TIM_Period = 199; //PWM Ƶ��=72000/(199+1)=36Khz//�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7199;//����������ΪTIMxʱ��Ƶ��Ԥ��Ƶֵ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, & TIM_TimeBaseInitStructure);

	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);//�ı�ָ���ܽŵ�ӳ�� ������F103�ο��ֲ��

	//PWM��ʼ��
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//PWM���ʹ��
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;

	TIM_OC1Init(TIM3,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);//ʹ�ܻ���ʧ��TIMx��CCR1�ϵ�Ԥװ�ؼĴ���
	TIM_Cmd(TIM3,ENABLE);//ʹ�ܻ���ʧ��TIMx����
}