/***************************************************************************************************************************************************
* @file: lcd4bit_driver.c
* @brief: This is lcd driver file contains function definitions for lcd opearation in 4 bit mode.
*
*
* @uthor: amar.shinde
* @created: 05/05/2023.
****************************************************************************************************************************************************/
#include"lcd4bit_driver.h"

void lcd4bit_init()
{
		PINSEL2 &= ~(1 << 3);	//P1.16-P1.26 as GPIO PORT
		IODIR1 = ( IODIR1 & ~( 0x7F << 17 )) | ( 0x7F << 17 );
		lcd4bit_cmd(0x03);
		lcd4bit_cmd(0x02);
		lcd4bit_cmd(0x28);
		lcd4bit_cmd(0x0C);
		lcd4bit_cmd(0x01);
}

void lcd4bit_cmd( uint8_t cmd )
{
			IOCLR1 = 0x7F << 16;
			IOSET1 = (cmd & 0xF0) << 16;
			IOCLR1 = RS;
			IOCLR1 = RW;
			IOSET1 = EN;
			delay_ms(5);
			IOCLR1 = EN;
	
			IOCLR1 = 0x7F << 17;
			IOSET1 = (cmd & 0x0F) << 20;
			IOCLR1 = RS;
			IOCLR1 = RW;
			IOSET1 = EN;
			delay_ms(5);
			IOCLR1 = EN;
}

void lcd4bit_data( uint8_t data )
{
			IOCLR1 = 0x7F << 16;
			IOSET1 = (data & 0xF0) << 16;
			IOSET1 = RS;
			IOCLR1 = RW;
			IOSET1 = EN;
			delay_ms(5);
			IOCLR1 = EN;
	
			IOCLR1 = 0x7F << 17;
			IOSET1 = (data & 0x0F) << 20;
			IOSET1 = RS;
			IOCLR1 = RW;
			IOSET1 = EN;
			delay_ms(5);
			IOCLR1 = EN;
}

void lcd4bit_string( char * str )
{
		while( *str != '\0' )
		{
				lcd4bit_data( *str );
				str++;
		}
}
