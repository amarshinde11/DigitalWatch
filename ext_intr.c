/********************************************************************************************************************************************
* @file: ext_intr.c
* @brief: This is driver file for external interrupts contain, interrupt service routines.
*
*	@uthor:amar.shinde
* @created: 05/05/2023.
*********************************************************************************************************************************************/
#include"ext_intr.h"

#if( EINT1_ENABLE == 1 )
/* ISR Routine for EINT1 */
void EINT1_Handler(void)__irq
{
		g_mode = SETTING;
		field++;
		TimerON();
		EXTINT = (1 << EINT1);
		VICVectAddr = 0;
}

void config_eint1( uint8_t mode, uint8_t pol )
{
		PINSEL0  &= ~(0x3 << 28);
		PINSEL0  |= (1 << 29);
		EXTMODE	 |= ( mode << 1 );
		EXTPOLAR |= ( pol << 1 );
}
#endif		//#if( EINT1_ENABLE == 1 )

#if( EINT2_ENABLE == 1 )
/* ISR Routine for EINT2 */
void EINT2_Handler(void)__irq
{
		if( (g_mode == SETTING) && (T1TC < _2SEC) ) {	
				set_flag = 1;	
				TimerON();
		}
		EXTINT = (1 << EINT2);	
		VICVectAddr = 0;
}

void config_eint2( uint8_t mode, uint8_t pol )
{
		PINSEL0  &= ~((uint32_t)0x3 << 30);
		PINSEL0  |= ((uint32_t)1 << 31);
		EXTMODE	 |= ( mode << 2 );
		EXTPOLAR |= ( pol << 2 );
}
#endif  //#if( EINT2_ENABLE == 1 )

#if( EINT0_ENABLE == 1 )
/* ISR Routine for EINT2 */
void EINT0_Handler(void)__irq
{
		//
		EXTINT = (1 << EINT0);	
		VICVectAddr = 0;
}

/* configuration setting for external interrupts */
void config_eint0( uint8_t mode, uint8_t pol )
{
		PINSEL1  &= ~0x3;
		PINSEL1  |= (1 << 0);
		EXTMODE	 |= ( mode << 0 );
		EXTPOLAR |= ( pol << 0 );
}
#endif		//#if( EINT0_ENABLE == 1 )


