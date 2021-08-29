#ifndef _DCMotor_H
#define _DCMotor_H
#include "stm32f10x.h"
#define in1 GPIO_Pin_4  	 
#define in2 GPIO_Pin_8
#define in3 GPIO_Pin_9  	  
#define in4 GPIO_Pin_10
#define SolValve GPIO_Pin_15
#define DC1 GPIO_Pin_12  	 
#define DC2 GPIO_Pin_13

void DC_Motor_init(void);



#endif
