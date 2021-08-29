#include "adc.h"

void adc_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO|RCC_APB2Periph_ADC1,ENABLE);

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//12M  ���14M ����ADCʱ�ӣ�ADCCLK��
	ADC_DeInit(ADC1);

	GPIO_InitStructure.GPIO_Pin=ADC_ZZ_LR|ADC_ZZ_UD|ADC_FZ_UD|ADC_FZ_LR;//ADC_FZ_LR|
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;	//ģ������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);


	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; 
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;; 
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; 
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; 
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 
	ADC_InitStructure.ADC_NbrOfChannel = 1; 
	ADC_Init(ADC1, &ADC_InitStructure);
	
	//����ָ��ADC�Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��



//	ADC_DiscModeChannelCountConfig(ADC1, 1);
//	ADC_DiscModeCmd(ADC1, ENABLE);

	ADC_Cmd(ADC1,ENABLE);	

	ADC_ResetCalibration(ADC1);//����ָ����ADC��У׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1));//��ȡADC����У׼�Ĵ�����״̬
	
	ADC_StartCalibration(ADC1);//��ʼָ��ADC��У׼״̬
	while(ADC_GetCalibrationStatus(ADC1));//��ȡָ��ADC��У׼����

//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//ʹ�ܻ���ʧ��ָ����ADC�����ת����������

}

u16 ReadADC()
{	
			float ad;
			u16 value=0;
			ADC_SoftwareStartConvCmd(ADC1, ENABLE);
			while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//ת��������־λ
			value=ADC_GetConversionValue(ADC1);//�������һ��ADCx�������ת�����	
//			value=value*360/4096;
//			value=(u16)(ad*1000);
			return value;

}
