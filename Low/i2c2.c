#include "main.h"

void I2C2_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitStructure.GPIO_Pin=I2C2_SCL|I2C2_SDA;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	I2C2_SCL_H;
	I2C2_SDA_H;
}
void I2C2_SDA_OUT(void)
{
GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=I2C2_SDA;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
void I2C2_SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=I2C2_SDA;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
void I2C2_Start(void)
{
	I2C2_SDA_OUT();
	
	I2C2_SDA_H;
	I2C2_SCL_H;
	US_Delay(5);
	I2C2_SDA_L;
	US_Delay(6);
	I2C2_SCL_L;
}
void I2C2_Stop(void)
{
	I2C2_SDA_OUT();

    I2C2_SCL_L;
    I2C2_SDA_L;
    I2C2_SCL_H;
    US_Delay(6);
    I2C2_SDA_H;
    US_Delay(6);
}
void I2C2_ACK(void)
{
	I2C2_SCL_L;
    I2C2_SDA_OUT();
    I2C2_SDA_L;
    US_Delay(2);
    I2C2_SCL_H;
    US_Delay(5);
    I2C2_SCL_L;
}
void I2C2_NACK(void)
{
	I2C2_SCL_L;
    I2C2_SDA_OUT();
    I2C2_SDA_H;
    US_Delay(2);
    I2C2_SCL_H;
    US_Delay(5);
    I2C2_SCL_L;
}
u8 I2C2_Wait_ACK(void)
{
	u8 tempTime=0;

	I2C2_SDA_IN();

	I2C2_SDA_H;
	US_Delay(1);
	I2C2_SCL_H;
	US_Delay(1);

	while(GPIO_ReadInputDataBit(GPIO_I2C2,I2C2_SDA))
	{
		tempTime++;
		if(tempTime>250)
		{
			I2C2_Stop();
			return 1;
		}	 
	}

	I2C2_SCL_L;
	return 0;
}
void I2C2_Write_Byte(u8 data)
{
	u8 i=0;

	I2C2_SDA_OUT();
	I2C2_SCL_L;//拉低时钟开始数据传输

	for(i=0;i<8;i++)
	{
		if((data&0x80)>0) //0x80  1000 0000
			I2C2_SDA_H;
		else
			I2C2_SDA_L;

		data<<=1;
		I2C2_SCL_H;
		US_Delay(2); //发送数据
		I2C2_SCL_L;
		US_Delay(2);
	}
}
u8 I2C2_Read_Byte(u8 ack)
{
	u8 i=0,receive=0;

   I2C2_SDA_IN();
   for(i=0;i<8;i++)
   {
   		I2C2_SCL_L;
		US_Delay(2);
		I2C2_SCL_H;
		receive<<=1;
		if(GPIO_ReadInputDataBit(GPIO_I2C2,I2C2_SDA))
		   receive++;
		US_Delay(1);	
   }

   	if(ack==0)
	   	I2C2_NACK();
	else
		I2C2_ACK();

	return receive;
}
