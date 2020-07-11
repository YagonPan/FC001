#include "main.h"

uint8_t OLED_GRAM[8][128];
uint8_t const DCB2HEX[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
void Oled_Init(void)
{
	Oled_Write_Command(0XAE);   
	Oled_Write_Command(0XD5);   
	Oled_Write_Command(0X80);   
	Oled_Write_Command(0X20);
	Oled_Write_Command(0X02);
	Oled_Write_Command(0XA8);
	Oled_Write_Command(0X3F);
	Oled_Write_Command(0XDA);
	Oled_Write_Command(0X12);
	
	Oled_Write_Command(0XA1);
	Oled_Write_Command(0XC8);
	
	Oled_Write_Command(0X40);
	Oled_Write_Command(0XD3);
	Oled_Write_Command(0X00);
	Oled_Write_Command(0X81);            //设置对比度
	Oled_Write_Command(0XCF);
	Oled_Write_Command(0XD9);
	Oled_Write_Command(0XF1);
	Oled_Write_Command(0XDB);
	Oled_Write_Command(0X20);
	Oled_Write_Command(0X8D);
	Oled_Write_Command(0X14);
	Oled_Write_Command(0XA4);
	
	Oled_Write_Command(0XA6);
	Oled_Write_Command(0XAF);	
	Oled_Cls(); 
	
}
void Oled_Write_Command(uint8_t Command)
{
	I2C2_Start();
	I2C2_Write_Byte(OLED_ADDR);
	I2C2_ACK();

	I2C2_Write_Byte(0x00);
	I2C2_ACK();
	I2C2_Write_Byte(Command);
	I2C2_ACK();
	I2C2_Stop();
}
void Oled_Write_Data(uint8_t data)
{
	I2C2_Start();
	I2C2_Write_Byte(OLED_ADDR);
	I2C2_ACK();

	I2C2_Write_Byte(0x40);
	I2C2_ACK();
	I2C2_Write_Byte(data);
	I2C2_ACK();
	I2C2_Stop();
}
void Oled_Page_Set(uint16_t page)
{
	Oled_Write_Command(0xB0+page);
}
void Oled_Column_Set(uint16_t column)
{
	Oled_Write_Command(0x00+(column%16));
	Oled_Write_Command(0x10|(column/16));
	//Oled_Write_Command(0x10|(column>>4));
	//Oled_Write_Command(0x00|(column&0x0f));
}
void OLed_Display_ON(void)
{
	Oled_Write_Command(0x8D);
	Oled_Write_Command(0x14);
	Oled_Write_Command(0xAF);
	MS_Delay(10);
}
void OLed_Display_OFF(void)
{
	Oled_Write_Command(0x8D);
	Oled_Write_Command(0x10);
	Oled_Write_Command(0xAF);
	MS_Delay(10);
}
void Oled_Refresh_Gram(void)
{
	uint16_t loop1, loop2;
	
	for(loop1=0;loop1<8;loop1++)   //   5
	{
		Oled_Page_Set(loop1);
		Oled_Column_Set(0x00);
		for(loop2=0; loop2<128; loop2++)    //128
		{
			Oled_Write_Data(OLED_GRAM[loop1][loop2]);
		}
	}
}
void Oled_Cls(void)
{
	uint16_t loop1, loop2;

	for(loop1=0; loop1<8; loop1++)
	{
		for(loop2=0; loop2<128; loop2++)
		{
			OLED_GRAM[loop1][loop2] = 0x00;
		}
	}
	Oled_Refresh_Gram();
}

void OLed_Draw_Point(uint16_t x, uint16_t y, uint8_t color)
{
	if(x>=128) return;
	if(y>=64)  return;

	//x = x+28;    //??????28
	if(color)
	{
		OLED_GRAM[y>>3][x] |= DCB2HEX[y&0x07];
	}
	else
	{
		OLED_GRAM[y>>3][x] &=~ DCB2HEX[y&0x07];
	}
}
void Oled_Draw_XLine(uint16_t x_start, uint16_t x_end, uint16_t y_location, uint8_t color)
{
	uint16_t length, loop;

	if(x_end > x_start)
	{
		length = x_end-x_start+1;

		for(loop = 0; loop < length; loop++)
		{
			OLed_Draw_Point(x_start+loop, y_location, color);
		}
	}
	else
	{
		length = x_start-x_end+1;

		for(loop = 0; loop < length; loop++)
		{
			OLed_Draw_Point(x_end+loop, y_location, color);
		}
	}
}
void Oled_Draw_YLine(uint16_t y_start, uint16_t y_end, uint16_t x_location, uint8_t color)
{
	uint16_t length, loop;

	if(y_end > y_start)
	{
		length = y_end-y_start+1;

		for(loop = 0; loop < length; loop++)
		{
			OLed_Draw_Point(x_location, y_start+loop, color);
		}
	}
	else
	{
		length = y_start-y_end+1;

		for(loop = 0; loop < length; loop++)
		{
			OLed_Draw_Point(x_location, y_end+loop, color);
		}
	}
}
