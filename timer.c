/**************************************************************************************************************************************
* @file: timer.c
*	@brief: This is driver file for Timer interrupt driver fuctions. 
*
* @uthor: amar.shinde
* @created: 05/05/2023.
**************************************************************************************************************************************/
#include"timer.h"

uint8_t read_flag;

void config_tmr0intr( uint32_t period )
{
		T0TCR = 0;
		T0PR  = (PCLK_15MHz-1);
		T0TC 	= T0PC = 0;
		T0MR0 = period;		/* match regiser set to period sec ( intr. on MR0 == TC )*/
		T0MCR |= (EN_INTR_MR0 | RESET_TC ); //Interrupt on MR0 
											/* an interrupt is generated when MR0 
												matches the value in the TC */
}

void TMR0_InterHandler()__irq
{
		if( T0IR & 1 )
		{
				read_flag = 1;
				T0IR |= 0x1;
		}			
		VICVectAddr = 0;
}


/* 	This fun gives time-bound to user for setting 
		time & date by pressing SW2 Before Time Elapse */
void TimerON()
{
		T1TCR = 0;
		T1TC = T1PC = 0;
		T1PR = (15000000-1);
		T1TCR = 1;
}

void EnablePeriodicTimer( uint8_t timer )
{
		switch( timer )
		{	
				case 0: T0TCR = 1; break;
				case 1: T1TCR = 1; break;
		}
}
void DisablePeriodicTimer( uint8_t timer )
{
		switch( timer )
		{	
				case 0: T0TCR &= ~(1); break;
				case 1: T1TCR &= ~(1); break;
		}
}
