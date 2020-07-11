#include "main.h"

void MPU6050_Write_Reg(u8 addr, u8 data)
{
	I2C1_Start();
	I2C1_Write_Byte(SLAADDR);
	I2C1_Wait_ACK();
	I2C1_Write_Byte(addr);
	I2C1_Wait_ACK();

	I2C1_Write_Byte(data);
	I2C1_Wait_ACK();
	I2C1_Stop();
}
u8 MPU6050_Read_Reg(u8 addr)
{
	u8 data;
	
	I2C1_Start();
	I2C1_Write_Byte(SLAADDR);
	I2C1_Wait_ACK();
	I2C1_Write_Byte(addr);
	I2C1_Wait_ACK();
	
	I2C1_Start();
	I2C1_Write_Byte(SLAADDR+1);
	I2C1_Wait_ACK();
	
	data = I2C1_Read_Byte(0);
	I2C1_Stop();
	
	return data;
}
void MPU6050_Init(void)
{
	MPU6050_Write_Reg(PWR_MGMT_1, 0x00);	//½â³ýÐÝÃß×´Ì¬
	MPU6050_Write_Reg(SMPLRT_DIV, 0x07);
	MPU6050_Write_Reg(CONFIG, 0x06);
	MPU6050_Write_Reg(GYRO_CONFIG, 0x18);
	MPU6050_Write_Reg(ACCEL_CONFIG, 0x1F);
}
void MPU6050_Read_ID(void)
{
	u8 id = 0;
	id = MPU6050_Read_Reg(WHO_AM_I);
	#ifdef _DEBUG_
	printf("MPU6050 ID is 0x%x\n", id);
	#endif
}

s32 MPU6050_Get_Data(u8 addr)
{
	u8 h_data, l_data;
	s32 data;
	s32 g_data;
	h_data = MPU6050_Read_Reg(addr);
	l_data = MPU6050_Read_Reg(addr+1);
	
	data = (s32)((h_data << 8)|l_data);
	g_data = data*16000/32768;
	
	return g_data;
}
