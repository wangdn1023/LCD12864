#include "key.h"
void key_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitStructure.GPIO_Pin=K_ZZ_UP|K_ZZ_DOWN|K_ZZ_LEFT|K_ZZ_RIGHT|K_FZ_UP|K_FZ_DOWN|K_FZ_LEFT|K_FZ_RIGHT;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//��������  //����ѡ�񸡿������������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
					
//	GPIO_ResetBits(GPIOA,K_UP);	//��K_UP��ʼ�����0
}

/*
void key_pros(u32 num,u32 num2)	  //����������
{

	if(k_up==1)	  //�жϰ���k_up�Ƿ���
	{
		delay_ms(10); //��������
		if(k_up==1)	 //�ٴ��жϰ���k_up�Ƿ���
		{
				GPIO_SetBits(GPIOA,in2|in3);
				GPIO_ResetBits(GPIOA,in1|in4);	
		}
//		while(k_up); //�ȴ������ɿ�
	}
	if(k_down==1)
	{
		delay_ms(10);
		if(k_down==1)
		{
			runStep_REV(num);		
		}
//		while(!k_down);
	}
}
*/

