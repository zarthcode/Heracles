/*
 * jtag.c
 *
 * Created: 7/31/2012 10:46:38 PM
 *  Author: Anthony
 */ 

#include "jtag.h"
#include <stdlib.h>

// Static global that contains the target device's TAP state.
static JTAGState_t currentState = RunTestIdle;
static bool unknownState = true;
static bool jtagEnabled = false;

static JTAGError_t errorState = OK;

static JTAGDevice_t Devices[JTAG_NUM_DEVICES];
static JTAGChain_t JTAGChain = {JTAG_NUM_DEVICES, Devices};

	
/// Returns the current JTAG state
JTAGState_t jtag_getState()
{
	
	if (unknownState)
	{
		// Error handling here.
		errorState = UnknownState;
	}
	else
	{
		errorState = OK;
	}
	
	return currentState;
}

/// Returns current error code.
JTAGError_t jtag_getLastError()
{
	return errorState;
}

/// Create a new device to the JTAG chain
void jtag_addDevice( uint8_t IDCode, uint8_t IRLength )
{
	errorState = OK;
	
	// Create the new device
	JTAGDevice_t* pNewDevice = malloc(sizeof(JTAGDevice_t));
	
	if (pNewDevice == NULL)
	{
		// Memory alloc failed!
		errorState = OutOfMemory;
		
		return;
	}
	
	// Configure the new device
	pNewDevice->IDCODE = IDCode;
	pNewDevice->IRLength = IRLength;
	pNewDevice->nextDevice = NULL;
	
	// Attach the new device to the end of the chain.
	if (JTAGChain.firstDevice == NULL)
	{
		JTAGChain.firstDevice = pNewDevice;
	} 
	else
	{
		// Navigate to the end of the chain
		JTAGDevice_t *pLastDevice = JTAGChain.firstDevice;
		
		while (pLastDevice->nextDevice != NULL)
		{
			pLastDevice = pLastDevice->nextDevice;
		}
		
		pLastDevice->nextDevice = pNewDevice;
	}
	
	JTAGChain.length++;
	
	
}

const JTAGChain_t* JTAG_Mode()
{
	/// \todo Implement JTAG_Mode

	// Configure JTAG pins
	bit_set(JTAG_DDR, BIT(JTAG_TMS));
	bit_set(JTAG_DDR, BIT(JTAG_TCK));
	bit_set(JTAG_DDR, BIT(JTAG_TDI));
	bit_clear(JTAG_DDR, BIT(JTAG_TDO));

	// Enable JTAG
	jtagEnabled = true;
	
	
	// Return device chain information
	return &JTAGChain;	
	
}

bool JTAG_isEnabled()
{	
	
	return jtagEnabled;
	
}

