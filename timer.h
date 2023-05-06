/**************************************************************************************************************************************
* @file: timer.h
*	@brief: This is header file for Timer interrupt driver fuctions. 
*
* @uthor: amar.shinde
* @created: 05/05/2023.
**************************************************************************************************************************************/
#ifndef __TIMER_H
#define __TIMER_H

#include<LPC21XX.H>
#include"ctypes.h"

#define 	PCLK_15MHz	( 15000000 )
#define 	EN_INTR_MR0	( 0x1 << 0 )
#define 	RESET_TC		( 0x1 << 1 )

#define 	TMR0				( 0 )
#define 	TMR1				( 1 )

/* interrupt after each _Xsec */
#define 	_1sec				( 1  )
#define 	_2sec				( 2  )
#define 	_5sec				( 5  )
#define 	_10sec			( 10 )

extern void TimerON(void);
extern void config_tmr0intr( uint32_t period );
extern void TMR0_InterHandler(void)__irq;
extern void EnablePeriodicTimer( uint8_t timer );
extern void DisablePeriodicTimer( uint8_t timer );

#endif 	//#ifndef __TIMER_H


