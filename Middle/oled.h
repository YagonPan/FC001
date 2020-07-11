#ifndef _OLED_H_
#define _OLED_H_
#include "main.h"
#include "stdint.h"
#define OLED_ADDR  		  0x78
#define OLED_COMMED       0x00                                  //write command
#define OLED_DATA         0x40                                  //write data

void Oled_Init(void);
void Oled_Write_Command(uint8_t Command);
void Oled_Write_Data(uint8_t data);
void Oled_Page_Set(uint16_t page);
void Oled_Column_Set(uint16_t column);
void OLed_Display_ON(void);
void OLed_Display_OFF(void);
void Oled_Refresh_Gram(void);
void Oled_Cls(void);

void OLed_Draw_Point(uint16_t x, uint16_t y, uint8_t color);
void Oled_Draw_XLine(uint16_t x_start, uint16_t x_end, uint16_t y_location, uint8_t color);
void Oled_Draw_YLine(uint16_t y_start, uint16_t y_end, uint16_t x_location, uint8_t color);

#endif
