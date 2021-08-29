#include "exti.h"

/*******************************************************************************
* �� �� ��         : exti_init
* ��������		   : �ⲿ�ж�2�˿ڳ�ʼ������	   
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void exti_init()  //�ⲿ�жϳ�ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure;

	EXTI_InitTypeDef EXTI_InitStructure;

	NVIC_InitTypeDef NVIC_InitStructure;

	/* ����GPIOʱ�� */
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

	//�˴�һ��Ҫ��ס���˿ڹܽż����ж��ⲿ��·
	/* �����ⲿ�жϵ�ģʽ */ 
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);//ѡ��GPIO�ܽ������ⲿ�ж���·	
	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
	EXTI_Init(&EXTI_InitStructure); 
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource6);//ѡ��GPIO�ܽ������ⲿ�ж���·	
	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
	EXTI_Init(&EXTI_InitStructure); 

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource7);//ѡ��GPIO�ܽ������ⲿ�ж���·	
	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
	EXTI_Init(&EXTI_InitStructure); 
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource8);//ѡ��GPIO�ܽ������ⲿ�ж���·
	EXTI_InitStructure.EXTI_Line=EXTI_Line8;
	EXTI_Init(&EXTI_InitStructure); 	
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource9);//ѡ��GPIO�ܽ������ⲿ�ж���·	
	EXTI_InitStructure.EXTI_Line=EXTI_Line9;
	EXTI_Init(&EXTI_InitStructure); 
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource10);//ѡ��GPIO�ܽ������ⲿ�ж���·	
	EXTI_InitStructure.EXTI_Line=EXTI_Line10;
	EXTI_Init(&EXTI_InitStructure); 
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);//ѡ��GPIO�ܽ������ⲿ�ж���·	
	EXTI_InitStructure.EXTI_Line=EXTI_Line11;
	EXTI_Init(&EXTI_InitStructure); 	
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12);//ѡ��GPIO�ܽ������ⲿ�ж���·	
	EXTI_InitStructure.EXTI_Line=EXTI_Line12;
	EXTI_Init(&EXTI_InitStructure); 

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource13);//ѡ��GPIO�ܽ������ⲿ�ж���·	
	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
	EXTI_Init(&EXTI_InitStructure); 
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);//ѡ��GPIO�ܽ������ⲿ�ж���·	
	EXTI_InitStructure.EXTI_Line=EXTI_Line14;
	EXTI_Init(&EXTI_InitStructure); 
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource15);//ѡ��GPIO�ܽ������ⲿ�ж���·	
	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
	EXTI_Init(&EXTI_InitStructure); 
	
//����NVIC���� 	


/*
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);		 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn; 	//��EXTI2��ȫ���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  //��Ӧ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		  //ʹ��
	NVIC_Init(&NVIC_InitStructure); 	
*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);		 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; 	//��EXTI2��ȫ���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		  //��Ӧ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		  //ʹ��
	NVIC_Init(&NVIC_InitStructure); 		

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn; 	//��EXTI2��ȫ���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		  //��Ӧ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		  //ʹ��
	NVIC_Init(&NVIC_InitStructure); 	

//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);		 
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn; 	//��EXTI2��ȫ���ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�Ϊ0
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		  //��Ӧ���ȼ�Ϊ0
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		  //ʹ��
//	NVIC_Init(&NVIC_InitStructure); 	

}
