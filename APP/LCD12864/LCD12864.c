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

/* 字符显示RAM地址    4行8列 */
u8 LCD_addr[4][8]={
	{0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87},  		//第一行
	{0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97},		//第二行
	{0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F},		//第三行
	{0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F}		//第四行
	};

void SendByte(u8 byte)
{
     u8 i; 
	  for(i = 0;i < 8;i++)
    {
			if((byte << i) & 0x80)  //0x80(1000 0000)  只会保留最高位
			{
				SID_H;           // 引脚输出高电平，代表发送1
			}
			else
			{
				SID_L;         // 引脚输出低电平，代表发送0
			}
		/*或		
			SID =	(Dbyte << i) & 0x80;
				
			上面那样为了方便理解
		*/
			SCLK_L;   //时钟线置低  允许SID变化
			delay_us(5); //延时使数据写入
			SCLK_H;    //拉高时钟，让从机读SID
//			delay_us(5); //延时使数据写入
		}   
}

void Lcd_WriteCmd(u8 Cmd )
{
     delay_ms(5);     //由于我们没有写LCD正忙的检测，所以直接延时1ms，使每次写入数据或指令间隔大于1ms 便可不用写忙状态检测
     SendByte(WRITE_CMD);            //11111,RW(0),RS(0),0   
     delay_ms(5); 
		 SendByte(0xf0&Cmd);      //高四位
     delay_ms(5); 
		 SendByte(Cmd<<4);   //低四位(先执行<<)
}

void Lcd_WriteData(u8 Dat )
{
//     delay_ms(5);     
     SendByte(WRITE_DAT);            //11111,RW(0),RS(1),0
//     delay_ms(5); 
		 SendByte(0xf0&Dat);      //高四位
//     delay_ms(5); 
		 SendByte(Dat<<4);   //低四位(先执行<<)
}

void Lcd_Init(void)
{ 
delay_ms(50);   	//等待液晶自检（延时>40ms）
	Lcd_WriteCmd(0x30);        //功能设定:选择基本指令集
delay_ms(1);//延时>100us
	Lcd_WriteCmd(0x02);        //功能设定:选择8bit数据流
delay_ms(1);	//延时>37us
    Lcd_WriteCmd(0x0c);        //开显示
delay_ms(1);	//延时>100us
    Lcd_WriteCmd(0x01);        //清除显示，并且设定地址指针为00H
delay_ms(30);	//延时>10ms
		Lcd_WriteCmd(0x06);        //进入设定点，初始化完成
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
		Lcd_WriteCmd(0x34);		//切换到扩充指令
		Lcd_WriteCmd(0x36);		//关闭图形显示
		Lcd_WriteCmd(0x3e);
		for(i = 0; i < 2; i++)   //上下屏写入
		{
			for(y=0;y<32;y++)   //垂直Y写32次
			{  
				Lcd_WriteCmd(lcd_y + y);		//行地址
				Lcd_WriteCmd(lcd_x);		//列地址
				for(x=0;x<16;x++)   //横向X写8次
				{
					Lcd_WriteData(*img ++);
				}
			}
			lcd_x=0x88;
		}
		Lcd_WriteCmd(0x36);//打开图形显示		
		Lcd_WriteCmd(0x30);        //切换回基本指令
	}	

void LCD_Clear(void)
	{
		Lcd_WriteCmd(0x01);			//清屏指令
		delay_ms(2);				//延时以待液晶稳定【至少1.6ms】
	}
	
