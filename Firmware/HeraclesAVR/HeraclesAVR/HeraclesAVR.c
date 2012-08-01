/*
 * HeraclesAVR.c
 *
 * Created: 7/19/2012 5:14:19 PM
 *  Author: Anthony
 */ 

#include "global.h"

#include <avr/io.h>
#include <util/delay.h>
#include "avrslcd.h"

int main(void)
{
	// Configure LCD Pins
	bit_set(DDRD, BIT(AVRSLCD_DATA));
	bit_set(DDRD, BIT(AVRSLCD_CLK));
	bit_set(DDRD, BIT(AVRSLCD_LATCH));
	bit_set(DDRD, BIT(AVRSLCD_RS));
	bit_set(DDRD, BIT(AVRSLCD_ENABLE));
	
	avrslcd_init(0,0,0);
	
	avrslcd_MoveCursor(1,4);
	printf("HERACLES");
	avrslcd_MoveCursor(2,1);
	printf("MOTION CONTROL");
	
	avrslcd_MoveCursor(1, 20);
	printf("Firmware");
	avrslcd_MoveCursor(2, 22);
	printf("0.1a");
	
	_delay_ms(10000);
	while(1)
	{

		avrslcd_CursorDisplayShift(1,0);
		_delay_ms(250);
	}
	
}