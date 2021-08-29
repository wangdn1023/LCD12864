#include "exti.h"

/*******************************************************************************
* 函 数 名         : exti_init
* 函数功能		   : 外部中断2端口初始化函数	   
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void exti_init()  //外部中断初始化
{
	GPIO_InitTypeDef GPIO_InitStructure;

	EXTI_InitTypeDef EXTI_InitStructure;

	NVIC_InitTypeDef NVIC_InitStructure;

	/* 开启GPIO时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitStructure.GPIO_Pin=k_left|k_right|k_up|k_down|k_left_co|k_right_co|k_ok_l|k_ok_r|k_set;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	 

	
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	EXTI_Init(&EXTI_InitStructure); 

	//此处一定要记住给端口管脚加上中断外部线路
	/* 设置外部中断的模式 */ 
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);//选择GPIO管脚用作外部中断线路	
	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
	EXTI_Init(&EXTI_InitStructure); 
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource6);//选择GPIO管脚用作外部中断线路	
	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
	EXTI_Init(&EXTI_InitStructure); 

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource7);//选择GPIO管脚用作外部中断线路	
	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
	EXTI_Init(&EXTI_InitStructure); 
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource8);//选择GPIO管脚用作外部中断线路
	EXTI_InitStructure.EXTI_Line=EXTI_Line8;
	EXTI_Init(&EXTI_InitStructure); 	
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource9);//选择GPIO管脚用作外部中断线路	
	EXTI_InitStructure.EXTI_Line=EXTI_Line9;
	EXTI_Init(&EXTI_InitStructure); 
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource10);//选择GPIO管脚用作外部中断线路	
	EXTI_InitStructure.EXTI_Line=EXTI_Line10;
	EXTI_Init(&EXTI_InitStructure); 
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);//选择GPIO管脚用作外部中断线路	
	EXTI_InitStructure.EXTI_Line=EXTI_Line11;
	EXTI_Init(&EXTI_InitStructure); 	
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12);//选择GPIO管脚用作外部中断线路	
	EXTI_InitStructure.EXTI_Line=EXTI_Line12;
	EXTI_Init(&EXTI_InitStructure); 

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource13);//选择GPIO管脚用作外部中断线路	
	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
	EXTI_Init(&EXTI_InitStructure); 
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);//选择GPIO管脚用作外部中断线路	
	EXTI_InitStructure.EXTI_Line=EXTI_Line14;
	EXTI_Init(&EXTI_InitStructure); 
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource15);//选择GPIO管脚用作外部中断线路	
	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
	EXTI_Init(&EXTI_InitStructure); 
	
//设置NVIC参数 	


/*
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);		 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn; 	//打开EXTI2的全局中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级为0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  //响应优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		  //使能
	NVIC_Init(&NVIC_InitStructure); 	
*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);		 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; 	//打开EXTI2的全局中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级为0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		  //响应优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		  //使能
	NVIC_Init(&NVIC_InitStructure); 		

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn; 	//打开EXTI2的全局中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级为0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		  //响应优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		  //使能
	NVIC_Init(&NVIC_InitStructure); 	

//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);		 
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn; 	//打开EXTI2的全局中断
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级为0
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		  //响应优先级为0
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		  //使能
//	NVIC_Init(&NVIC_InitStructure); 	

}
