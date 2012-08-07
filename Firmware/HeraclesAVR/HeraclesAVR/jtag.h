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

#define JTAG_TMS			5
#define JTAG_TCK			4
#define JTAG_TDI			7
#define JTAG_TDO			6

// Support for nTRST/ seems unnecessary

/// JTAG States
typedef enum
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
} JTAGState_t;

typedef enum JTAGError
{
	OK = 1,
	UnknownState,
	OutOfMemory,
	InvalidRequest,
	DeviceOutOfRange,
	DataWidthOutOfRange
} JTAGError_t;

/// JTAG Device-chain descriptor
typedef struct JTAGDevice
{
	uint8_t IRLength;
	uint8_t IDCODE;
	struct JTAGDevice* nextDevice;
} JTAGDevice_t;

/// JTAG device chain description
typedef struct
{
	uint8_t length;
	JTAGDevice_t* firstDevice;
} JTAGChain_t;

/// Returns current error code.
JTAGError_t jtag_getLastError();

/// Returns the current JTAG state.
JTAGState_t jtag_getState();

/// Navigates to the requested JTAG state
void jtag_setState(JTAGState_t state);

/// Sends data to the specified device
void jtag_sendData(uint8_t* pData, uint8_t length, uint8_t device);

/// Create a new device to the JTAG chain
void jtag_addDevice(uint8_t IDCode, uint8_t IRLength);

