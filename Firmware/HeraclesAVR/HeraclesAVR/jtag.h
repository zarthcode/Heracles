/**
 * jtag.h
 *
 * Created: 7/31/2012 10:46:18 PM
 *  Author: Anthony
 *
 */ 

#pragma once
#include <stdbool.h>
#include <avr/io.h>

// Use different pins during debug?

#define JTAG_PORT	PORTF
#define JTAG_DDR	DDRF

#define TMS			5
#define TCK			4
#define TDI			7
#define TDO			6

#define TRST


/// JTAG States
enum JTAGState
{
	TestLogicReset = 0,
	RunTestIdle,
	SelectDRScan,
	CaptureDR,
	ShiftDR,
	Exit1DR,
	PauseDR,
	Exit2DR,
	UpdateDR,
	SelectIRScan,
	CaptureIR,
	ShiftIR,
	Exit1IR,
	PauseIR,
	Exit2IR,
	UpdateIR
};

/// JTAG Device-chain descriptor
struct JTAGDevice 
{
	uint8_t IRLength;
	uint8_t IDCODE;
};

/// Navigates to the requested jtag state (shortest path)
JTAGState nextState(JTAGState currentState, bool bTMS);

/// Returns the current JTAG state.
JTAGState getState();

//