#include "LCD12864.h"
#include "systick.h"

void lcd_GPIO_init()
{
       
  GPIO_InitTypeDef  GPIO_InitStructure;


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
/*
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
*/
  SID_H;
  SCLK_H;
}

/* �ַ���ʾRAM��ַ    4��8�� */
u8 LCD_addr[4][8]={
	{0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87},  		//��һ��
	{0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97},		//�ڶ���
	{0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F},		//������
	{0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F}		//������
	};

void SendByte(u8 byte)
{
     u8 i; 
	  for(i = 0;i < 8;i++)
    {
			if((byte << i) & 0x80)  //0x80(1000 0000)  ֻ�ᱣ�����λ
			{
				SID_H;           // ��������ߵ�ƽ��������1
			}
			else
			{
				SID_L;         // ��������͵�ƽ��������0
			}
		/*��		
			SID =	(Dbyte << i) & 0x80;
				
			��������Ϊ�˷������
		*/
			SCLK_L;   //ʱ�����õ�  ����SID�仯
			delay_us(5); //��ʱʹ����д��
			SCLK_H;    //����ʱ�ӣ��ôӻ���SID
//			delay_us(5); //��ʱʹ����д��
		}   
}

void Lcd_WriteCmd(u8 Cmd )
{
     delay_ms(5);     //��������û��дLCD��æ�ļ�⣬����ֱ����ʱ1ms��ʹÿ��д�����ݻ�ָ��������1ms ��ɲ���дæ״̬���
     SendByte(WRITE_CMD);            //11111,RW(0),RS(0),0   
     delay_ms(5); 
		 SendByte(0xf0&Cmd);      //����λ
     delay_ms(5); 
		 SendByte(Cmd<<4);   //����λ(��ִ��<<)
}

void Lcd_WriteData(u8 Dat )
{
//     delay_ms(5);     
     SendByte(WRITE_DAT);            //11111,RW(0),RS(1),0
//     delay_ms(5); 
		 SendByte(0xf0&Dat);      //����λ
//     delay_ms(5); 
		 SendByte(Dat<<4);   //����λ(��ִ��<<)
}

void Lcd_Init(void)
{ 
delay_ms(50);   	//�ȴ�Һ���Լ죨��ʱ>40ms��
	Lcd_WriteCmd(0x30);        //�����趨:ѡ�����ָ�
delay_ms(1);//��ʱ>100us
	Lcd_WriteCmd(0x02);        //�����趨:ѡ��8bit������
delay_ms(1);	//��ʱ>37us
    Lcd_WriteCmd(0x0c);        //����ʾ
delay_ms(1);	//��ʱ>100us
    Lcd_WriteCmd(0x01);        //�����ʾ�������趨��ַָ��Ϊ00H
delay_ms(30);	//��ʱ>10ms
		Lcd_WriteCmd(0x06);        //�����趨�㣬��ʼ�����
}

void LCD_Display_Words(unsigned char row, unsigned char column, unsigned char *str)
{
	unsigned char n=0,a;
	Lcd_WriteCmd(LCD_addr[row][column]);  		
    while (*str != '\0')  				
    {
		Lcd_WriteData(*str++);  		
		n++;
 
		if((n+2*column)%16==0)
		{
			a=(n+2*column)/16;
			if(row==0)
			{
			if(a==1)
				Lcd_WriteCmd(0x90);
			if(a==2)
				Lcd_WriteCmd(0x88);
			if(a==3)
				Lcd_WriteCmd(0x98);
			if(a==4)
				Lcd_WriteCmd(0x80);
			}
 
			if(row==1)
			{
			if(a==1)
				Lcd_WriteCmd(0x88);
			if(a==2)
				Lcd_WriteCmd(0x98);
			if(a==3)
				Lcd_WriteCmd(0x80);
			if(a==4)
				Lcd_WriteCmd(0x90);
			}	
 
			if(row==2)
			{
			if(a==1)
				Lcd_WriteCmd(0x98);
			if(a==2)
				Lcd_WriteCmd(0x80);
			if(a==3)
				Lcd_WriteCmd(0x90);
			if(a==4)
				Lcd_WriteCmd(0x88);
			}	
 
			if(row==3)
			{
			if(a==1)
				Lcd_WriteCmd(0x80);
			if(a==2)
				Lcd_WriteCmd(0x90);
			if(a==3)
				Lcd_WriteCmd(0x88);
			if(a==4)
				Lcd_WriteCmd(0x98);
			}		
		}
    }
}

void LCD_Display_Picture(uint8_t *img)
	{
		uint8_t x,y,i,lcd_x=0x80,lcd_y=0x80;
		Lcd_WriteCmd(0x34);		//�л�������ָ��
		Lcd_WriteCmd(0x36);		//�ر�ͼ����ʾ
		Lcd_WriteCmd(0x3e);
		for(i = 0; i < 2; i++)   //������д��
		{
			for(y=0;y<32;y++)   //��ֱYд32��
			{  
				Lcd_WriteCmd(lcd_y + y);		//�е�ַ
				Lcd_WriteCmd(lcd_x);		//�е�ַ
				for(x=0;x<16;x++)   //����Xд8��
				{
					Lcd_WriteData(*img ++);
				}
			}
			lcd_x=0x88;
		}
		Lcd_WriteCmd(0x36);//��ͼ����ʾ		
		Lcd_WriteCmd(0x30);        //�л��ػ���ָ��
	}	

void LCD_Clear(void)
	{
		Lcd_WriteCmd(0x01);			//����ָ��
		delay_ms(2);				//��ʱ�Դ�Һ���ȶ�������1.6ms��
	}
	
