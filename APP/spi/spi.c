#include "spi.h"
void SPI1_Init()  //SPI1初始化
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef	 SPI_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);//打开SPI1时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;		//PB13 PB14 PB15	   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	 //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);			     
	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);  //拉高
/*	
	SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex; //	SPI 设置为双线双向全双工
	SPI_InitStructure.SPI_Mode=SPI_Mode_Master;	//设置SPI为主模式
	SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b;	//设置SPI数据大小为8位
	SPI_InitStructure.SPI_CPOL=SPI_CPOL_High;	//设置SPI默认时钟悬空为高电平
	SPI_InitStructure.SPI_CPHA=SPI_CPHA_2Edge;	//设置SPI数据捕获在第二个时钟沿
	SPI_InitStructure.SPI_NSS=SPI_NSS_Soft;	//设置SPI NSS管脚由软件管理
	SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_256;	//设置SPI 波特率预分频值为 256
	SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB;	//设置SPI 数据从高位传输
	SPI_InitStructure.SPI_CRCPolynomial=7;	//设置SPI CRC值计算的多项式
	SPI_Init(SPI1,&SPI_InitStructure);	
*/
	SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex; //	SPI 设置为双线双向全双工
	SPI_InitStructure.SPI_Mode=SPI_Mode_Master;	//设置SPI为主模式
	SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b;	//设置SPI数据大小为8位
	SPI_InitStructure.SPI_CPOL=SPI_CPOL_Low;	//设置SPI默认时钟悬空为高电平
	SPI_InitStructure.SPI_CPHA=SPI_CPHA_1Edge;	//设置SPI数据捕获在第二个时钟沿
	SPI_InitStructure.SPI_NSS=SPI_NSS_Soft;	//设置SPI NSS管脚由软件管理
	SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_16;	//设置SPI 波特率预分频值为 256
	SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB;	//设置SPI 数据从高位传输
	SPI_InitStructure.SPI_CRCPolynomial=7;	//设置SPI CRC值计算的多项式
	SPI_Init(SPI1,&SPI_InitStructure);		
		
	SPI_Cmd(SPI1,ENABLE); //使能SPI1			
}

u8 SPI1_ReadWriteByte(u8 dat)		 //SPI1读写一个字节
{
	u8 t;
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==RESET)	//等待发送缓存器空
	{
		t++;
		if(t>=200)return 0;	//超时返回错误标志	
	}
	SPI_I2S_SendData(SPI1,dat); //发送数据
	t=0;
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)==RESET)	//等待接收
	{
		t++;
		if(t>=200)return 0;	//超时返回错误标志	
	}
	return SPI_I2S_ReceiveData(SPI1); //返回最近SPI1接收的数据			
}
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)	//设置SPI1的速度
{
	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));	
	SPI1->CR1&=0XFFC7;		 //修改BR[2:0]值
	SPI1->CR1|=SPI_BaudRatePrescaler;	//设置SPI1速度 
	SPI_Cmd(SPI1,ENABLE);			
}

