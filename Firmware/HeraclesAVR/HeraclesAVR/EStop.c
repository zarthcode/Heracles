/*
 * EStop.c
 *
 * Created: 9/12/2012 1:00:00 AM
 *  Author: Anthony
 */ 
#include <avr/io.h>

#include "EStop.h"
#include "Pinout.h"
#include "global.h"



static bool bESTOP_State = true;

bool ESTOP_isActive()
{
	
	// Return state of the ESTOP_IN pin.
	return bESTOP_State;
	
}




bool ESTOP_Clear()
{
	/// \todo Implement ESTOP_Clear
	
	bESTOP_State = false;
	
	// Return ESTOP State
	return bit_get(PIN_ESTOP_PORT, BIT(PIN_ESTOP_IN));
	
}


void ESTOP_Set()
{
	/// \todo Implement ESTOP_Set
	
	bit_set(PIN_ESTOP_PORT, BIT(PIN_ESTOP_OUT));
	
	
	
	
}

void ESTOP_handle()
{
	
	// Send USB interrupt message that ESTOP has been set.
	
}
