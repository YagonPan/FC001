/******************************************************************************
**@file:    main.c
**@author:  Peter Pan
**@version: V-001
**@date:    6-Jul-2019
**@brief:   This is a main file.
******************************************************************************/
#include "main.h"

int main()
{
	
	All_Init();
	
	while(1)
	{
		//MS_Delay(5000);
		
		MPU6050_Read_ID();
		
		printf("ACCEL_XOUT:%d\n", MPU6050_Get_Data(ACCEL_XOUT_H));
		printf("ACCEL_YOUT:%d\n", MPU6050_Get_Data(ACCEL_YOUT_H));
		printf("ACCEL_ZOUT:%d\n", MPU6050_Get_Data(ACCEL_ZOUT_H));
		
		//printf("GYRO_XOUT:%f\n", MPU6050_Get_Data(GYRO_XOUT_H));
		//printf("GYRO_YOUT:%f\n", MPU6050_Get_Data(GYRO_YOUT_H));
		//printf("GYRO_ZOUT:%f\n", MPU6050_Get_Data(GYRO_ZOUT_H));
		
		MS_Delay(1000);
	}
	

}
