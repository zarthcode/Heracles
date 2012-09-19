/*
 * EStop.h
 *
 * Created: 9/12/2012 12:19:55 AM
 *  Author: Anthony
 */ 


#pragma once

#include <stdbool.h>

/// Returns TRUE if there is an Emergency stop condition
bool ESTOP_isActive();

/// Attempts to clear the ESTOP condition - returns current ESTOP state.
bool ESTOP_Clear();

/// Sets an ESTOP condition
void ESTOP_Set();

/// ESTOP Interrupt Service Routine
void ESTOP_handle();

