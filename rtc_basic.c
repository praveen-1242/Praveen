#include <LPC21xx.H>

#include "lcd.h"
#include "lcd_defines.h"


#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)

#define PREINT_VAL ((int)((PCLK / 32768) - 1))
#define PREFRAC_VAL (PCLK - ((PREINT_VAL+1)*32768))

int main()
{
	//RTC Disable & reset the RTC CTC
	CCR = (1<<1);
	
	//1 sec tick time using PREINT & PREFRAC
	PREINT = PREINT_VAL;
	PREFRAC = PREFRAC_VAL;
	
	//enable the RTC
	CCR = (1<<0);
	
	Init_LCD();
	
	HOUR = 20;
	MIN = 25;
	SEC = 0;
	DOM = 17;
	MONTH = 10;
	YEAR = 2025;
	
	while(1)
	{
		CmdLCD(GOTO_LINE1_POS0);
		CharLCD((HOUR/10)+48);
		CharLCD((HOUR%10)+48);
		CharLCD(':');
		CharLCD((MIN/10)+0x30);
		CharLCD((MIN%10)+0x30);
		CharLCD(':');
		CharLCD((SEC/10)+'0');
		CharLCD((SEC%10)+'0');
		
		CmdLCD(GOTO_LINE2_POS0);
		CharLCD((DOM/10)+48);
		CharLCD((DOM%10)+48);
		CharLCD('/');
		CharLCD((MONTH/10)+0x30);
		CharLCD((MONTH%10)+0x30);
		CharLCD('/');
		U32LCD(YEAR);			
	}
}
