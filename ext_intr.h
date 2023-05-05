/********************************************************************************************************************************************
* @file: ext_intr.h
* @brief: This is header file for external interrupt contains, interrupt service routines prototype,  
*					macro-definitions for External interrupt Settings EXTMODE, EXTPOLAR etc.
*
*	@uthor:amar.shinde
* @created: 05/05/2023.
*********************************************************************************************************************************************/
#ifndef _EXT_INTR_H
#define _EXT_INTR_H

#include<LPC21XX.H>
#include"digi_watch.h"
#include"timer.h"
#include"ctypes.h"

#define EINT0_ENABLE		( 0 )
#define EINT1_ENABLE		( 1 )
#define EINT2_ENABLE		( 1 )
#define EINT3_ENABLE		( 0 )

/* external interrupts */
#define EINT0						( 0 )
#define EINT1	  				( 1 )
#define EINT2						( 2 )
#define EINT3	  				( 3 )

/* external interrupt mode */
#define LEVEL_SENSITIVE ( 0 )
#define EGDE_SENSITIVE  ( 1 )

/* external interrupt polarity */
#define LOW_ACTIVE			( 0 )
#define HIGH_ACTIVE			( 1 )

/* giving 2 sec time to press the switch */
#define _2SEC						( 2 )

extern void EINT1_Handler(void)__irq;
extern void EINT2_Handler(void)__irq;
extern void EINT0_Handler(void)__irq;
extern void EINT3_Handler(void)__irq;
extern void config_eint0( uint8_t mode, uint8_t pol );
extern void config_eint1( uint8_t mode, uint8_t pol );
extern void config_eint2( uint8_t mode, uint8_t pol );
extern void config_eint3( uint8_t mode, uint8_t pol );

#endif 		//#ifndef _EXT_INTR_H


