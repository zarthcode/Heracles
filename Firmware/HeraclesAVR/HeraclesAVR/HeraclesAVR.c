/*
 * HeraclesAVR.c
 *
 * Created: 7/19/2012 5:14:19 PM
 *  Author: Anthony
 */ 

#include "global.h"

#include <avr/io.h>
#include <util/delay.h>

#include "LUFA/Common/Common.h"
#include "LUFA/Drivers/USB/USB.h"

#include "USB/USBImpl.h"


#include "LCD/avrslcd.h"

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
	_delay_ms(2000);
	
	
	// Initialize USB
	USB_Init();

	// Enable global interrupts
	sei();
	
	// Main loop
	while(1)
	{
	
		ServiceUSB();
	
	}
	
}

