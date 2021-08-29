#include "key.h"
void key_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitStructure.GPIO_Pin=K_ZZ_UP|K_ZZ_DOWN|K_ZZ_LEFT|K_ZZ_RIGHT|K_FZ_UP|K_FZ_DOWN|K_FZ_LEFT|K_FZ_RIGHT;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入  //不能选择浮空输入否则会出错
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
					
//	GPIO_ResetBits(GPIOA,K_UP);	//对K_UP初始化输出0
}

/*
void key_pros(u32 num,u32 num2)	  //按键处理函数
{

	if(k_up==1)	  //判断按键k_up是否按下
	{
		delay_ms(10); //消抖处理
		if(k_up==1)	 //再次判断按键k_up是否按下
		{
				GPIO_SetBits(GPIOA,in2|in3);
				GPIO_ResetBits(GPIOA,in1|in4);	
		}
//		while(k_up); //等待按键松开
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

