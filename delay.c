/***************************************************************************************************************************
* @file: delay.c
* @brief: This is source file contains, Timer delay function definitions.
*
* @uthor: amar.shinde
* @created: 29/04/2023.
****************************************************************************************************************************/
#include"delay.h"

void delay_ms( uint32_t ms )
{
		T1TC = T1PC = 0;
		T1PR = (15000-1);
		T1TCR = 1;
		while( T1TC < ms );
		T1TCR = 0;
}

void delay_sec( uint32_t sec )
{
		T1TC = T1PC = 0;
		T1PR = (15000000-1);
		T1TCR = 1;
		while( T1TC < sec );
		T1TCR = 0;
}

