#ifndef _key_H
#define _key_H
#include "stm32f10x.h"
#define K_ZZ_UP 		GPIO_Pin_8 
#define K_ZZ_DOWN 	GPIO_Pin_9 
#define K_ZZ_LEFT 	GPIO_Pin_10 
#define K_ZZ_RIGHT 	GPIO_Pin_11 
#define K_FZ_UP 		GPIO_Pin_12
#define K_FZ_DOWN 	GPIO_Pin_13 
#define K_FZ_LEFT 	GPIO_Pin_14 
#define K_FZ_RIGHT 	GPIO_Pin_15 

#define k_zz_up 		GPIO_ReadInputDataBit(GPIOB,K_ZZ_UP)		  //获取按键的状态
#define k_zz_down 	GPIO_ReadInputDataBit(GPIOB,K_ZZ_DOWN)
#define k_zz_left 	GPIO_ReadInputDataBit(GPIOB,K_ZZ_LEFT)
#define k_zz_right 	GPIO_ReadInputDataBit(GPIOB,K_ZZ_RIGHT)
#define k_fz_up 		GPIO_ReadInputDataBit(GPIOB,K_FZ_UP)		  //获取按键的状态
#define k_fz_down 	GPIO_ReadInputDataBit(GPIOB,K_FZ_DOWN)
#define k_fz_left 	GPIO_ReadInputDataBit(GPIOB,K_FZ_LEFT)
#define k_fz_right 	GPIO_ReadInputDataBit(GPIOB,K_FZ_RIGHT)


void key_init(void);


#endif
