/***************************************************************************************************************************************************
* @file: digi_watch.h
* @brief: This is header file for digital watch using I2C Based TRC DS1307.
*
* @uthor: amar.shinde
* @created: 05/05/2023.
****************************************************************************************************************************************************/
#ifndef DIGI_WATCH_H
#define DIGI_WATCH_H

#include<LPC21XX.H>
#include"ctypes.h"

#define PCLK_15MHz		( 15000000 )
#define _100Kbps			( 100000  )
#define _400Kbps			( 400000  )

#define RTC_BIT_RATE	( _100Kbps )
#define RTC_SL_ADR		( 0xD0 )

#define RUNNING				( 0 )
#define UPDATE				( 1 )
#define SETTING				( 2 )

#define _24HRS				( 0 )
#define _12HRS				( 1 )
#define CLK_MODE    	( _12HRS )

#define REG_SEC				( 0 )
#define REG_MIN				( 1 )
#define REG_HRS				( 2 )
#define REG_DAY				( 3 )
#define REG_DOM				( 4 )
#define REG_MON				( 5 )
#define REG_YRS				( 6 )

enum DAYS_WEEK
{
	SUN = 1, MON, TUE, WED, THUR, FRI, SAT,
};

enum MONTHS_YEAR
{
	JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEPT, OCT, NOV, DEC
};

extern uint8_t g_hh, g_mm, g_ss;
extern uint8_t g_day, g_date, g_mon, g_year;
extern uint8_t g_mode;
extern uint8_t field;
extern uint8_t set_flag;

void RTC_init( void );
void RTC_Set_Time( uint8_t mem, uint8_t time );
void RTC_Set_Date( uint8_t mem, uint8_t date );
void RTC_UpdateSettings( uint8_t clk_mode );
void RTC_Read_Time(void);
void RTC_Read_Date(void);
void RTC_SendToLcd(void);
void RTC_SendToUart(void);
void Update_Seconds(void);
void Update_Minutes(void);
void Update_Hours( uint8_t clk_mode );
void Update_AMPM(uint8_t clk_mode);
void Update_Month(void);
void Update_Year(void);
void Upadte_DayOfMonth(void);
void Update_DaysOfWeek(void);

#endif   //#ifndef DIGI_WATCH_H
