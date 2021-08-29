#ifndef _adc_H
#define _adc_H
#include "stm32f10x.h"
#define ADC_ZZ_LR GPIO_Pin_0  	 
#define ADC_ZZ_UD GPIO_Pin_1
#define ADC_FZ_LR GPIO_Pin_2  	  
#define ADC_FZ_UD GPIO_Pin_3

void adc_init(void);

u16 ReadADC();


#endif
