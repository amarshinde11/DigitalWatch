/***************************************************************************************************************************************************
* @file: lcd4bit_driver.h
* @brief: This is header file for lcd driver contains function prototypes for lcd opearation in 4 bit mode.
*
* @uthor: amar.shinde
* @created: 05/05/2023.
****************************************************************************************************************************************************/
#ifndef LCD4BIT_DRIVER_H
#define LCD4BIT_DRIVER_H

#include<LPC21XX.H>
#include"ctypes.h"
#include"delay.h"

#define RS    (1 << 17)
#define RW		(1 << 18)
#define EN		(1 << 19)
void lcd4bit_init( void );
void lcd4bit_data( uint8_t data );
void lcd4bit_cmd( uint8_t cmd );
void lcd4bit_string( char * str );

#endif //#ifndef LCD4BIT_DRIVER_H

