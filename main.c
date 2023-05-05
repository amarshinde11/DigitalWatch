/******************************************************************************************************************
* @file: main.c
* @brief: Thus is main file contain main function to call peripheral initialization functions 
*					i.e. i2c_init(), config_eintX(), uart_init(), lcd4bit_init(), configure vectored interrupts, etc.
*					Also continuous reading of TRC Time & Date and printing onto Display as well as Serial Terminal.
*
* @uthor: amar.shinde
* @created: 03/05/2023.
********************************************************************************************************************/
#include"lcd4bit_driver.h"
#include"uart_driver.h"
#include"digi_watch.h"
#include"ext_intr.h"
#include"config_vic.h"
#include"timer.h"
#include"ctypes.h"

uint8_t g_hh, g_mm, g_ss;	/* sec, min, hours */				
uint8_t g_day, g_date, g_mon, g_year;	/* Date Variables */
uint8_t g_mode;		/* mode of operation, Setting, Updation or Running */
uint8_t field;		/* the field want to update */
uint8_t set_flag;	/* Switch Press flag for RTC Setting */

int main()
{
		uart0_init( 9600 );	/* initialize uart0 to print Time & Date on serial terminal */
		lcd4bit_init();			/* initialize LCD to print Time & Date 16*2 LCD */
		//RTC_init();					/* init. RTC1307 ( RTC_init initialzes i2c controller ) */
		
		/* initialize External Interrupt for Switch Press for Time & Date Settings */
		config_eint1( EGDE_SENSITIVE, LOW_ACTIVE );
		config_eint2( EGDE_SENSITIVE, LOW_ACTIVE );
		config_tmr0intr( _1sec );
	
		/* initialize the VIC Table for EXT. Interrupt to be served */
		config_vic( INTR_EINT1, EINT1_Handler, SLOT0 );
		config_vic( INTR_EINT2, EINT2_Handler, SLOT1 );
		config_vic( INTR_TMR0,  TMR0_InterHandler, SLOT3 );
		Irq_Intr_Enable( INTR_EINT1 );	/* Enable the EINT1 on SW1 */
		Irq_Intr_Enable( INTR_EINT2 );	/* Enable the EINT2 on SW2 */
		Irq_Intr_Enable( INTR_TMR0 );		/* Enable the TMR0 interrupt on Match */
		EnablePeriodicTimer( TMR0 );
	
		while(1)
		{
				if( g_mode == SETTING ) /* SW1 is pressed, Enter into Setting Mode */
				{
						if( set_flag == 1 ) /* if SW2 is pressed in 2 sec, flag will be set */
						{
							Irq_Intr_Disable( INTR_TMR0 );
							switch( field )	/* SW1 is Pressed for selecting the Setting Fields */
							{
									case 1: Update_Seconds(); 				break;
									case 2: Update_Minutes();		 			break;
									case 3: Update_Hours( CLK_MODE ); break;
									case 4: Update_AMPM( CLK_MODE ); 	break;
									case 5: Update_DaysOfWeek(); 			break;
									case 6: Upadte_DayOfMonth(); 			break;
									case 7: Update_Month();						break;
									case 8: Update_Year();						break;
							}
							set_flag = 0;
						}
						else if( T1TC == _2SEC ) {	/* if none of Switch is pressed then Enter into UPDATE Mode,
																		to update whatever Settings Done till now */
							g_mode = UPDATE;	
						}
				}
				else if( g_mode == UPDATE ) {	/* RTC Regs. Updation Mode After Settings */
						RTC_UpdateSettings( CLK_MODE );
						g_mode = RUNNING;			/* Change The mode to Running Mode to Read & Display the RTC Clock */
						field  = 0;
						Irq_Intr_Enable( INTR_TMR0 );
						EnablePeriodicTimer( TMR0 );
				}
				else if( g_mode == RUNNING ) {	/* Running Mode (default mode or selected after updation of settings) */
							if( read_flag )
							{
									//RTC_Read_Time();		/* read Time fields from RTC */
									//RTC_Read_Date();		/* read Date fields from RTC */
									RTC_SendToUart();		/* Print onto UART0 */
									RTC_SendToLcd();		/* Print onto LCD Display */
									read_flag = 0;
							}
				}
		}	
}

