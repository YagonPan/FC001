#ifndef _I2C2_H_
#define _I2C2_H_
#include "main.h"

#define GPIO_I2C2     GPIOB

#define I2C2_SCL_H GPIO_SetBits(GPIO_I2C2,I2C2_SCL)
#define I2C2_SCL_L GPIO_ResetBits(GPIO_I2C2,I2C2_SCL)

#define I2C2_SDA_H GPIO_SetBits(GPIO_I2C2,I2C2_SDA)
#define I2C2_SDA_L GPIO_ResetBits(GPIO_I2C2,I2C2_SDA)

void I2C2_init(void);
void I2C2_SDA_OUT(void);
void I2C2_SDA_IN(void);
void I2C2_Start(void);
void I2C2_Stop(void);
void I2C2_ACK(void);
void I2C2_NACK(void);
u8 I2C2_Wait_ACK(void);
void I2C2_Write_Byte(u8 data);
u8 I2C2_Read_Byte(u8 ack);
#endif

