/*
 * FatalError.c
 *
 * Created: 8/27/2012 8:43:02 AM
 *  Author: Anthony
 */ 
#include "global.h"
#include "LCD/avrslcd.h"
#include <util/delay.h>

void FatalError(char* str)
{
	
	avrslcd_Clear();
	avrslcd_MoveCursor(1, 3);
	printf("FATAL ERROR:");
	avrslcd_MoveCursor(2, 1);
	printf(str);
	
	while(1)
	{
		_delay_ms(400);
		avrslcd_CursorDisplayShift(1,0);		
		
	}
	
}