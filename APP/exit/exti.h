#ifndef _exti_H
#define _exti_H
#include "stm32f10x.h"

#define k_set	 				GPIO_Pin_5 
#define k_ok_r	 			GPIO_Pin_6  //PA2
#define k_ok_l 				GPIO_Pin_7  //K1 PE2

#define k_left 			GPIO_Pin_8  //PA2
#define k_right 		GPIO_Pin_9  //K1 PE2
#define k_up 				GPIO_Pin_10  //K1 PE2
#define k_down 			GPIO_Pin_11  //K1 PE2

#define k_left_co 	GPIO_Pin_12  //PA2
#define k_right_co 	GPIO_Pin_13  //K1 PE2
#define k_up_co 		GPIO_Pin_14  //K1 PE2
#define k_down_co 	GPIO_Pin_15  //K1 PE2

void exti_init(void);  //外部中断初始化


#endif 
