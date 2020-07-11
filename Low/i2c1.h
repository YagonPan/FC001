#ifndef _I2C1_H_
#define _I2C1_H_

#include "main.h"

#define GPIO_I2C1     GPIOB

#define I2C1_SCL_H GPIO_SetBits(GPIO_I2C1,I2C1_SCL)
#define I2C1_SCL_L GPIO_ResetBits(GPIO_I2C1,I2C1_SCL)

#define I2C1_SDA_H GPIO_SetBits(GPIO_I2C1,I2C1_SDA)
#define I2C1_SDA_L GPIO_ResetBits(GPIO_I2C1,I2C1_SDA)

void I2C1_init(void);
void I2C1_SDA_OUT(void);
void I2C1_SDA_IN(void);
void I2C1_Start(void);
void I2C1_Stop(void);
void I2C1_ACK(void);
void I2C1_NACK(void);
u8 I2C1_Wait_ACK(void);
void I2C1_Write_Byte(u8 data);
u8 I2C1_Read_Byte(u8 ack);

#endif

