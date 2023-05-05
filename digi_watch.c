/*****************************************************************************************************
* @file: digi_watch.c
* @brief: This is driver file, contains driver functions to initialize I2C Slave RTC-DS1307,
*					RTC_Set_Time, RTC_Set_Date, RTC_Read_Time, RTC_Read_Date, 
*
* @uthor: amar.shinde
* @created: 04/05/2023.
*******************************************************************************************************/
#include"digi_watch.h"
#include"uart_driver.h"
#include"i2c_driver.h"
#include"lcd4bit_driver.h"

void Update_Seconds()
{
			switch( g_ss ) {
					case 0x09:		g_ss = 0x10; break;
					case 0x19:		g_ss = 0x20; break;
					case 0x29:		g_ss = 0x30; break;
					case 0x39:		g_ss = 0x40; break;
					case 0x49:		g_ss = 0x50; break;
					case 0x59:		g_ss = 0x00; break;
					default  :    g_ss++;			
			}
			lcd4bit_cmd(0x01);
			lcd4bit_data( (g_ss / 0x10) + 48);
			lcd4bit_data( (g_ss % 0x10) + 48);
}

void Update_Minutes()
{
			switch( g_mm ) {
					case 0x09:		g_mm = 0x10; 	break;
					case 0x19:		g_mm = 0x20; 	break;
					case 0x29:		g_mm = 0x30; 	break;
					case 0x39:		g_mm = 0x40; 	break;
					case 0x49:		g_mm = 0x50; 	break;
					case 0x59:		g_mm = 0x00; 	break;
					default  :    g_mm++;				
			}
			lcd4bit_cmd(0x01);
			lcd4bit_data( (g_mm / 0x10) + 48);
			lcd4bit_data( (g_mm % 0x10) + 48);
}

void Update_Hours( uint8_t clk_mode )
{
			if( clk_mode == _12HRS ) {
				switch( g_hh ) {
						case 0x09:		g_hh = (0x10); 	break;
						case 0x12:		g_hh = (0x00); 	break;
						default  :    g_hh++;				
				}
				g_hh |= (1 << 6);
			}
			else {
					switch( g_hh ) {
							case 0x09:		g_hh = 0x10; 	break;
							case 0x19:		g_hh = 0x20; 	break;
							case 0x23:		g_hh = 0x00; 	break;
							default  :    g_hh++;				
					}
			}
			lcd4bit_cmd(0x01);
			lcd4bit_data( ((g_hh&0x1F) / 0x10) + 48);
			lcd4bit_data( ((g_hh&0x1F) % 0x10) + 48);
}

void Update_AMPM( uint8_t clk_mode )
{
		if( clk_mode == _12HRS ) {
				switch( ((g_hh >> 5)&1) )
				{	
						case 0: g_hh |=  (1 << 5); break;
						case 1: g_hh &= ~(1 << 5); break;
				}
				lcd4bit_cmd(0x89);
				if( ((g_hh >> 5)&1) )
					lcd4bit_data('P');
				else
					lcd4bit_data('A');
		}
}

void Update_DaysOfWeek()
{
		if( g_day == 7 )
			g_day = 1;
		else
			g_day++;
		lcd4bit_cmd(0x01);
		switch( g_day ) {
				case 1: lcd4bit_string("SUN"); break;
				case 2: lcd4bit_string("MON"); break;
				case 3: lcd4bit_string("TUE"); break;
				case 4: lcd4bit_string("WED"); break;
				case 5: lcd4bit_string("THUR"); break;
				case 6: lcd4bit_string("FRI"); break;
				case 7: lcd4bit_string("SAT"); break;			
		}
}

void Upadte_DayOfMonth()
{
		switch( g_date ) {
				case 0x09:	g_date = 0x10;	break;
				case 0x19:  g_date = 0x20;	break;
				case 0x29:	g_date = 0x30;	break;
				default:    g_date++;				
		}
		lcd4bit_cmd(0x01);
		lcd4bit_data( (g_date / 0x10) + 48);
		lcd4bit_data( (g_date % 0x10) + 48);
}

void Update_Month()
{
		switch( g_mon ) {
				case 0x09: g_mon = 0x10;	break;
				case 0x12: g_mon = JAN;		break;
				default:   g_mon++;				
		}
		lcd4bit_cmd(0x01);
		lcd4bit_data( (g_mon / 0x10) + 48);
		lcd4bit_data( (g_mon % 0x10) + 48);
}

void Update_Year()
{
		switch( g_year ) {
				case 0x09: 	g_year = 0x10;	break;
				case 0x19:	g_year = 0x20;	break;
				case 0x29: 	g_year = 0x30;	break;
				case 0x39:	g_year = 0x40;	break;
				case 0x49: 	g_year = 0x50;	break;
				case 0x59:	g_year = 0x60;	break;
				case 0x69: 	g_year = 0x70;	break;
				case 0x79:	g_year = 0x80;	break;
				case 0x89: 	g_year = 0x90;	break;
				case 0x99:	g_year = 0x00;	break;
				default:    g_year++;	
		}
		lcd4bit_cmd(0x01);
		lcd4bit_data( (g_year / 0x10) + 48);
		lcd4bit_data( (g_year % 0x10) + 48);
}

void RTC_UpdateSettings( uint8_t clk_mode )
{
		if( clk_mode == _12HRS )
				g_hh |= (1 << 6); 
		RTC_Set_Date( REG_DAY, g_day );
		RTC_Set_Date( REG_DOM, g_date );
		RTC_Set_Date( REG_MON, g_mon );
		RTC_Set_Date( REG_YRS, g_year );
		RTC_Set_Time( REG_HRS, g_hh );
		RTC_Set_Time( REG_MIN, g_mm );
		RTC_Set_Time( REG_SEC, g_ss );
}

void RTC_init( void )
{
		/* RTC Default Settings */
		g_hh = 0x00, g_mm = 0x00, g_ss = 0x00;
		g_day  = THUR, g_date = 0x04; 
		g_mon  = MAY,  g_year = 0x23;
		i2c_init( _100Kbps );
		RTC_UpdateSettings( CLK_MODE );
}

void RTC_Set_Date( uint8_t mem, uint8_t date )
{
		i2c_Byte_Write( RTC_SL_ADR, mem, date);
}

void RTC_Set_Time( uint8_t mem, uint8_t time )
{
		i2c_Byte_Write( RTC_SL_ADR, mem, time);
}


void RTC_Read_Time(void)
{
		g_ss = i2c_Byte_Read( RTC_SL_ADR, REG_SEC );			
		if( g_ss == 0x00 )
				g_mm = i2c_Byte_Read( RTC_SL_ADR, REG_MIN );
		if( g_mm == 0x00 )
				g_hh = i2c_Byte_Read( RTC_SL_ADR, REG_HRS );
}

void RTC_Read_Date(void)
{
		if( ((g_hh>>5&1)==0) && 	/* if AM/PM bit is 0 */
				((g_hh & 0x1F) == 0) ) /* And Hours Register have value 0x00 then only need to read the date & day register */
		{
				g_day 	= i2c_Byte_Read( RTC_SL_ADR, REG_DAY );
				g_date 	= i2c_Byte_Read( RTC_SL_ADR, REG_DOM );
		}
		if( (g_date >= 0x28) && 			/* if DOM is 28th to 31st */
				((g_hh & 0x1F) == 0) )  	/*And hours register is 0 then only need to read month values */
		{		
				g_mon 	= i2c_Byte_Read( RTC_SL_ADR, REG_MON );
		}
		if( (g_mon == 12) && 			/* check if is it a 12th month(DEC) */
				(g_date == 0x31) && 	/* check if is it a last 31st date */
				((g_hh & 0x1F) == 0) ) /* check if is it 0x00 hrs in Hours register */
		{
				g_year 	= i2c_Byte_Read( RTC_SL_ADR, REG_YRS );
		}
}

void RTC_SendToUart()
{
		uart0_tx_string("\n\rTime: ");
		uart0_tx( (g_hh&0x1F) / 0x10);
		uart0_tx( (g_hh&0x1F) % 0x10);
		uart0_tx(':');
		uart0_tx(g_mm/0x10);
		uart0_tx(g_mm%0x10);
		uart0_tx(':');
		uart0_tx(g_ss/0x10);
		uart0_tx(g_ss%0x10);
		if( (g_hh >> 5) & 1 )
				uart0_tx_string(" PM");
		else
				uart0_tx_string(" AM");
		
		uart0_tx_string("\n\rDate: ");
		
		switch( g_day )
		{
				case 1: uart0_tx_string(" SUN, "); break;
				case 2: uart0_tx_string(" MON, "); break;
				case 3: uart0_tx_string(" TUE, "); break;
				case 4: uart0_tx_string(" WED, "); break;
				case 5: uart0_tx_string(" THUR, "); break;
				case 6: uart0_tx_string(" FRI, "); break;
				case 7: uart0_tx_string(" SAT, "); break;			
		}
		uart0_tx(g_date/0x10);
		uart0_tx(g_date%0x10);
		uart0_tx('/');
		uart0_tx(g_mon/0x10);
		uart0_tx(g_mon%0x10);
		uart0_tx('/');
		uart0_tx_string("20");
		uart0_tx(g_year/0x10);
		uart0_tx(g_year%0x10);
}

void RTC_SendToLcd()
{
		lcd4bit_cmd(0x01);
		lcd4bit_data((g_hh&0x1F)/0x10);
		lcd4bit_data((g_hh&0x1F)%0x10);
		lcd4bit_data(':');
		lcd4bit_data(g_mm/0x10);
		lcd4bit_data(g_mm%0x10);
		lcd4bit_data(':');
		lcd4bit_data(g_ss/0x10);
		lcd4bit_data(g_ss%0x10);
		if( (g_hh >> 5) & 1 )
				lcd4bit_data('P');
		else
				lcd4bit_data('A');
		lcd4bit_cmd(0x8B);
		switch( g_day )
		{
				case 1: lcd4bit_string("SUN"); break;
				case 2: lcd4bit_string("MON"); break;
				case 3: lcd4bit_string("TUE"); break;
				case 4: lcd4bit_string("WED"); break;
				case 5: lcd4bit_string("THUR"); break;
				case 6: lcd4bit_string("FRI"); break;
				case 7: lcd4bit_string("SAT"); break;			
		}
	
		lcd4bit_cmd(0xC0);
		lcd4bit_data(g_date/0x10);
		lcd4bit_data(g_date%0x10);
		lcd4bit_data('/');
		lcd4bit_data(g_mon/0x10);
		lcd4bit_data(g_mon%0x10);
		lcd4bit_data('/');
		lcd4bit_string("20");
		lcd4bit_data(g_year/0x10);
		lcd4bit_data(g_year%0x10);
}











