#ifndef __lcd12864_H_
#define __lcd12864_H_

#include "stm32f10x.h" 

#define WRITE_CMD	0xF8//Ð´ÃüÁî  
#define WRITE_DAT	0xFA//Ð´Êý¾Ý

#define SID_H  GPIO_SetBits(GPIOB,GPIO_Pin_0) 
#define SID_L  GPIO_ResetBits(GPIOB,GPIO_Pin_0) 
#define SCLK_H  GPIO_SetBits(GPIOB,GPIO_Pin_1) 
#define SCLK_L  GPIO_ResetBits(GPIOB,GPIO_Pin_1) 


void lcd_GPIO_init(void);
void Lcd_Init(void);

void SendByte(u8 Dbyte);
void LCD_Clear(void);
void LCD_Display_Words(uint8_t x,uint8_t y,uint8_t*str);
void LCD_Display_Picture(uint8_t *img);

void Lcd_WriteData(u8 Dat );
void Lcd_WriteCmd(u8 Cmd );

#endif
