/***************************************************************************************************************************
* @file: config_vic.h
* @brief: This is header file contains, Vectored Interrupt Controller Config function declarations
*					enum for VIC Slots, macro-definitions for interrupt numbers etc.
* @uthor: amar.shinde
* @created: 29/04/2023.
****************************************************************************************************************************/
#ifndef _CONFIG_VIC_H
#define _CONFIG_VIC_H

#include<LPC21XX.H>
#include"ctypes.h"

/* UART Interrupt configuration */
#define INTR_WDT		( 0 )

/* Timer0/1 overflow interrupt number */
#define INTR_TMR0		( 4 )
#define INTR_TMR1		( 5 )

/* UART0/UART1 Interrupt number */
#define INTR_UART0 	( 6 )
#define INTR_UART1	( 7 )

/* PWM/Timer Match Interrupt number */
#define INTR_PWM		( 8 )
#define INTR_MATCH	( 8 )

/* I2C Interrupt number */
#define INTR_I2C		( 9 )

/* SPI Interrupt number */
#define INTR_SPI0		( 10 )
#define INTR_SPI1		( 11 )

/* SYNC Serial Port Interrupt number */
#define INTR_SSP		( 11 )

/* PLL Lock Interrupt */
#define INTR_PLL		( 12 )

/* RTC Interrupt number */
#define INTR_RTC		( 13 )

/* Enternal Interrupt number */
#define INTR_EINT0		( 14 )
#define INTR_EINT1		( 15 )
#define INTR_EINT2		( 16 )
#define INTR_EINT3		( 17 )

/* ADC Interrupt number */
#define INTR_ADC	  	( 18 )

/* CAN controller TX intrrupt number */
#define INTR_CAN_COM ( 19 )
#define INTR_CAN1_TX ( 20 )
#define INTR_CAN2_TX ( 21 )
#define INTR_CAN3_TX ( 22 )
#define INTR_CAN4_TX ( 23 )

/* CAN controller RX intrrupt number */
#define INTR_CAN1_RX ( 26 )
#define INTR_CAN2_RX ( 27 )
#define INTR_CAN3_RX ( 28 )
#define INTR_CAN4_RX ( 29 )

typedef enum INTR_PRIORITIES {	/* VIC Slots */
		SLOT0, SLOT1, SLOT2, SLOT3, SLOT4,
		SLOT5, SLOT6, SLOT7, SLOT8, SLOT9,
		SLOT10, SLOT11, SLOT12, SLOT13, SLOT14,
		SLOT15
}SLOTS_e;

void Irq_Intr_Enable( uint32_t intr_no );
void Irq_Intr_Disable( uint32_t intr_no );
void config_vic( uint32_t intr_no, void(*IntrHandler)(void)__irq, uint32_t slot_no );

#endif //#ifndef _CONFIG_VIC_H
