#include"i2c_driver.h"
#include"digi_watch.h"

void i2c_init( uint32_t BitRate )
{
		uint32_t clk_div = 0;
		PINSEL0 = ((PINSEL0 & ~(0xF << 4)) | (I2SCL | I2SDA));
		clk_div = (PCLK_15MHz / BitRate);
		I2SCLL  = (clk_div / 2);
		I2SCLH	= (clk_div / 2);
		I2CONSET = I2EN;
}

void i2c_Byte_Write( uint8_t sa, uint8_t mem, uint8_t data )
{
		I2CONSET = I2STA;
		while( SI == 0 );
		if( I2STAT != 0x8 ) {
				I2CONCLR = I2SIC;
		}
		
		I2DAT = sa;
		I2CONCLR = I2SIC;
		while( SI == 0 );
		if( I2STAT != 0x18 ) {
			I2CONCLR = (I2STO | I2SIC);
		}
		
		I2DAT = mem;
		I2CONCLR = I2SIC;
		while( SI == 0 );
		if( I2STAT != 0x28 ) {
			I2CONCLR = (I2SIC | I2STO);
		}
		
		I2DAT = data;
		I2CONCLR = I2SIC;
		while( SI == 0 );
		if( I2STAT != 0x28 ) {
			I2CONCLR = (I2SIC | I2STO);
		}
		I2CONCLR = (I2SIC | I2STO);
}

uint8_t i2c_Byte_Read( uint8_t sa, uint8_t mem )
{
		uint8_t data;
		I2CONSET = I2STA;			/* Start Condition */
		while( SI == 0 );
		if( I2STAT != 0x8 ) {	/* return if Start Cond. not generated */
				I2CONCLR = I2SIC;
				return 0;
		}
		
		I2DAT = sa;					/* send slave address */
		I2CONCLR = I2SIC;		/* clear i2c interrupt flag */
		while( SI == 0 );
		if( I2STAT != 0x18 ) {	/* go ahead, if slave address matched & received  ACK, else return */
			I2CONCLR = (I2STO | I2SIC);
			return 0;
		}
		
		I2DAT = mem;				/* send the memmory address to read */
		I2CONCLR = I2SIC;
		while( SI == 0 );
		if( I2STAT != 0x28 ) { /* go ahead, if selected an appropriate register to read */
			I2CONCLR = (I2SIC | I2STO);
			return 0;
		}
		
		I2CONCLR = I2SIC;		/* clear SI interrupt flag before Repeated Start */
		I2CONSET = I2STA;		/* generate Repeated Start Condition */
		while( SI == 0 );
		if( I2STAT != 0x10 ) {	/* go ahead if, repeated start condition generated successfully */
				I2CONCLR = (I2SIC | I2STO);
				return 0;
		}
		
		I2DAT = (sa | RD);	/* send the slave address + read mode */
		I2CONCLR = I2SIC;		/* clear the SI flag */
		
		while( SI == 0 );	
		I2CONCLR = I2SIC;
		if( I2STAT != 0x40 ) {	/* go ahead, if ACK on slave address match + read mode */
				I2CONCLR = (I2STO | I2SIC);
				return 0;
		}
		
		while( SI == 0 );		/* wait for data receive in I2DAT reg & assert SI Flag */
		data = I2DAT;				/* read seconds in local variable */
		if( I2STAT != 0x58 ) { 
				I2CONCLR = (I2SIC | I2STO);
				return 0;
		}
		I2CONCLR = (I2SIC | I2STO);
		return data;
}



