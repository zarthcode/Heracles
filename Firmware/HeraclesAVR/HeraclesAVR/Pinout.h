/*
 * Pinout.h
 *
 * Created: 9/12/2012 1:04:09 AM
 *  Author: Anthony
 */ 

#pragma once


#define PIN_ESTOP_PORT	PORTD
#define PIN_ESTOP_DDR	DDRD

/// Monitors the status of the ESTOP chain
#define PIN_ESTOP_IN	1

/// Forces an ESTOP state
#define PIN_ESTOP_OUT	0