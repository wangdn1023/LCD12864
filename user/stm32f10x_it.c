/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "DCMotor.h"
#include "systick.h"
#include "public.h"


/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/*
void EXTI3_IRQHandler()	   //外部中断2中断函数
{
//	u16 adc4,adc5,adc6,adc7;
//	unsigned char b[3]={'0','0','0'};
//	static int flag=0;
	if(EXTI_GetITStatus(EXTI_Line3)==SET)
	{
   		EXTI_ClearITPendingBit(EXTI_Line3);//清除EXTI线路挂起位
		delay_ms(10);//消抖处理
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)==Bit_RESET)	   //k_left按键按下
		{
			delay_ms(10);//消抖处理
			GPIO_SetBits(GPIOA,in1|in2);				
/*			ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_239Cycles5);	
			adc4=ReadADC();	
			
			b[0]='0';
			b[1]='0';
			b[2]='0';		

			b[0]=b[0]+adc4/100%10;
			b[1]=b[1]+adc4/10%10;
			b[2]=b[2]+adc4%10;

			LCD_Display_Words(1,2,b);
			delay_ms(10);
			
		if(adc4==0)
			{
				GPIO_SetBits(GPIOA,in2);
				GPIO_ResetBits(GPIOA,in1);	
			}
		if(adc4==360)
			{
				GPIO_SetBits(GPIOA,in1);
				GPIO_ResetBits(GPIOA,in2);	
			}
		
			
		}

		} 
}		
*/
extern u8 tx_buf[9];	
	
void EXTI9_5_IRQHandler()	   //外部中断2中断函数
{
	extern int l_auto,r_auto,save;
	static int sum=0,sum1=0,sum3=0;	
	if(EXTI_GetITStatus(EXTI_Line5)==SET)
	{
   	EXTI_ClearITPendingBit(EXTI_Line5);//清除EXTI线路挂起位
		delay_ms(10);//消抖处理
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==Bit_RESET)	   //k_left按键按下
		{
			delay_ms(10);//消抖处理	
			sum3++;				
			if(sum3==1)
			{
				save=3;
			tx_buf[1]=tx_buf[1]|0x04;		//save01			
			}
			if(sum3==2)
			{
				save=4;
			tx_buf[1]=tx_buf[1]|0x08;		//save10			
			}
			if(sum3==3)
			{
				save=1;
			tx_buf[1]=tx_buf[1]|0x0c;		//save11			
			}
			if(sum3==4)
			{
				save=2;				
				sum3=0;
			tx_buf[1]=tx_buf[1]&0xf3;		//save00			
			}	
		} 
	}		
	
	if(EXTI_GetITStatus(EXTI_Line6)==SET)
	{
   	EXTI_ClearITPendingBit(EXTI_Line6);//清除EXTI线路挂起位
		delay_ms(10);//消抖处理
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==Bit_RESET)	   //k_left按键按下
		{
			delay_ms(10);//消抖处理			
			if(sum1==0)
			{
				r_auto=1;
				sum1++;		
			tx_buf[1]=tx_buf[1]|0x01;					
			}
			else
			{
				r_auto=0;
				sum1=0;
			tx_buf[1]=tx_buf[1]&0xfe;						
			}		
		} 
	}		
	
	if(EXTI_GetITStatus(EXTI_Line7)==SET)
	{
   		EXTI_ClearITPendingBit(EXTI_Line7);//清除EXTI线路挂起位
		delay_ms(10);//消抖处理
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==Bit_RESET)	   //k_left按键按下
		{
			delay_ms(10);//消抖处理
			if(sum==0)
			{
				l_auto=1;
				sum++;	
			tx_buf[1]=tx_buf[1]|0x02;				
			}
			else
			{
				l_auto=0;
				sum=0;
			tx_buf[1]=tx_buf[1]&0xfd;					
			}		
		} 
	}		
	if(EXTI_GetITStatus(EXTI_Line8)==SET)
	{
   		EXTI_ClearITPendingBit(EXTI_Line8);//清除EXTI线路挂起位
		delay_ms(10);//消抖处理
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==Bit_RESET)	   //k_left按键按下
		{
			delay_ms(10);//消抖处理
			tx_buf[0]=tx_buf[0]|0x01;
		} 
	}	
	if(EXTI_GetITStatus(EXTI_Line9)==SET)
	{
   		EXTI_ClearITPendingBit(EXTI_Line9);//清除EXTI线路挂起位
		delay_ms(10);//消抖处理
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==Bit_RESET)	   //k_left按键按下
		{
			delay_ms(10);//消抖处理
			tx_buf[0]=tx_buf[0]|0x02;
		} 
	}		
}

void EXTI15_10_IRQHandler()	   //外部中断2中断函数
{
	if(EXTI_GetITStatus(EXTI_Line10)==SET)
	{
   		EXTI_ClearITPendingBit(EXTI_Line10);//清除EXTI线路挂起位
		delay_ms(10);//消抖处理
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)==Bit_RESET)	   //k_left按键按下
		{
			delay_ms(10);//消抖处理
			tx_buf[0]=tx_buf[0]|0x04;		
		} 
	}	
	
	if(EXTI_GetITStatus(EXTI_Line11)==SET)
	{
   		EXTI_ClearITPendingBit(EXTI_Line11);//清除EXTI线路挂起位
		delay_ms(10);//消抖处理
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==Bit_RESET)	   //k_left按键按下
		{
			delay_ms(10);//消抖处理
			tx_buf[0]=tx_buf[0]|0x08;		
		} 
	}		
	
	if(EXTI_GetITStatus(EXTI_Line12)==SET)
	{
   		EXTI_ClearITPendingBit(EXTI_Line12);//清除EXTI线路挂起位
		delay_ms(10);//消抖处理
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==Bit_RESET)	   //k_left按键按下
		{
			delay_ms(10);//消抖处理
			tx_buf[0]=tx_buf[0]|0x10;
		} 
	}	

	if(EXTI_GetITStatus(EXTI_Line13)==SET)
	{
   		EXTI_ClearITPendingBit(EXTI_Line13);//清除EXTI线路挂起位
		delay_ms(10);//消抖处理
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==Bit_RESET)	   //k_left按键按下
		{
			delay_ms(10);//消抖处理
			tx_buf[0]=tx_buf[0]|0x20;
		} 
	}		

	if(EXTI_GetITStatus(EXTI_Line14)==SET)
	{
   		EXTI_ClearITPendingBit(EXTI_Line14);//清除EXTI线路挂起位
		delay_ms(10);//消抖处理
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==Bit_RESET)	   //k_left按键按下
		{
			delay_ms(10);//消抖处理
			tx_buf[0]=tx_buf[0]|0x40;
		} 
	}	

	if(EXTI_GetITStatus(EXTI_Line15)==SET)
	{
   		EXTI_ClearITPendingBit(EXTI_Line15);//清除EXTI线路挂起位
		delay_ms(10);//消抖处理
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==Bit_RESET)	   //k_left按键按下
		{
			delay_ms(10);//消抖处理
			tx_buf[0]=tx_buf[0]|0x80;
		} 
	}		

}

void TIM3_IRQHandler()	 //定时器3中断函数
{
	extern int time1s;	
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	time1s=1;
}

