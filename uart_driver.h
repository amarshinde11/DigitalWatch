/***************************************************************************************************************************
* @file: uart_driver.h
* @brief: This is uart_driver header file, contains uart driver function prototypes, macro-definitions  
*
* @uthor: amar.shinde
* @created: 29/04/2023.
****************************************************************************************************************************/
#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include<LPC21XX.H>
#include"ctypes.h"

#define PCLK_15MHz	( 15000000 )
#define PCLK_30MHz	( 30000000 )
#define PCLK_60MHz	( 60000000 )

/* uart 0 configuration */
#define UART0				( 0 )
#define TxD0				( 1 << 0 )
#define RxD0				( 1 << 2 )
#define THRE0				( (U0LSR >> 5) & 1 )
#define RDR0				( (U0LSR & 1) )

/* uart 1 configuration */
#define UART1				( 1 )
#define TxD1				( 1 << 16 )
#define RxD1				( 1 << 18 )
#define THRE1				( (U1LSR >> 5) & 1 )
#define RDR1				( (U1LSR & 1) )

/* Baud Rate & Data Length ( UxLCR ) */
#define DLAB 				( 1 << 7 )
#define DATA_5BIT		( 0x0 )
#define DATA_6BIT		( 0x1 )
#define DATA_7BIT		( 0x2 )
#define DATA_8BIT		( 0x3 )

#define UART0_INT_ENABLE  ( 0 )
#define UART1_INT_ENABLE  ( 0 )
/* uart interrupts */
void Uart0_IRQ_Handler(void)__irq;
void Uart1_IRQ_Handler(void)__irq;
void config_uart_interrupt( uint8_t uart_no );

/* UART0 driver fun  prototypes */
void uart0_init( uint32_t baud );
void uart0_tx_string( char * str );
void uart0_tx( uint8_t data );
uint8_t uart0_rx( void );
void uart0_integer( int32_t int_num );
void uart0_float( float f_val );
void uart0_rx_string( char * str, uint32_t size );

/* UART1 driver fun  prototypes */
void uart1_init( uint32_t baud );
void uart1_tx_string( char * str );
void uart1_tx( uint8_t data );
uint8_t uart1_rx( void );
void uart1_integer( int32_t int_num );
void uart1_float( float f_val );
void uart1_rx_string( char * str, uint32_t size );

#endif  //#ifndef UART_DRIVER_H
