/*
 * USBImpl.c
 *
 * Created: 8/7/2012 8:50:32 PM
 *  Author: Anthony
 */ 
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "USBImpl.h"
#include "USBCommand.h"
#include "Endpoints.h"

#include "global.h"
#include "LCD/avrslcd.h"
#include <stddef.h>

static bool returnFire = false;
static uint8_t delayed = 0;

char BulkBuffer[32];
uint16_t BulkBufferData = 0;

char IsoBuffer[8];
uint16_t IsoBufferData = 0;

/// Performs USB endpoint tasks.
void ServiceUSB(void)
{
	
	if (USB_DeviceState != DEVICE_STATE_Configured)
		return;
	
	// Save endpoint
	uint8_t PrevEndpoint = Endpoint_GetCurrentEndpoint();
	
	// Check for interrupts
	Endpoint_SelectEndpoint(INTERRUPT_OUT_EPNUM);
		
	if(Endpoint_IsOUTReceived())
	{
		
		
		if (ESTOP_isActive())
		{
		
		
			// JTAG Mode
			if (JTAG_isEnabled())
			{
			
				// Receive JTAG Command
				
				
				// Dispatch command
				
			
			}
		
		
		
		}
		else
		{
			
			
			unsigned char interruptData[16];
			memset(interruptData, '\0', 16);
			
			// Process incoming interrupt packet.
			Endpoint_Read_Stream_LE(interruptData, 16, NULL);
			
			// Acknowledge the packet
			if (!Endpoint_IsReadWriteAllowed())
			{
				// ACK
				Endpoint_ClearOUT();
			}
			
			avrslcd_MoveCursor(2,1);
			printf("%s", interruptData);
			
			returnFire = true;
		}		
	}

	
	Endpoint_SelectEndpoint(INTERRUPT_IN_EPNUM);
	
	// Test interrupt function
	if(!Endpoint_IsConfigured() || !Endpoint_IsEnabled())
	{
		FatalError("Endpoint 2 not configured (interrupt in).");
	}
	
	
	// Send return interrupt.
	// if (Endpoint_WaitUntilReady() == ENDPOINT_READYWAIT_NoError)		// Causes a spin-wait!
	if (Endpoint_IsINReady())
	{			
			
		if (!returnFire || (delayed < 2))
		{
			if(returnFire)
				delayed++;
								
			// No interrupt pending
			//	Endpoint_ClearIN();		// Omitting this could lead to a timeout, eventually.
			Endpoint_AbortPendingIN();	// NAK a few times, just to prove that it's okay.
		}
		else
		{
				
			// Process outgoing interrupt packet.
			
			// Prepare/get data structure to write
			
				
			// Write data
			wchar_t Buffer[6] = L"PONG!";
			Endpoint_Write_Stream_LE(Buffer, 12, NULL);
				
			// Acknowledge the packet
			Endpoint_ClearIN();

			avrslcd_Clear();
			printf("Delayed %dx", delayed);

			returnFire = false;
			delayed = 0;
				
		}
	}
		
	
	// Check for bulk data
	Endpoint_SelectEndpoint(BULK_OUT_EPNUM);
	if(Endpoint_IsOUTReceived())
	{
		// Process incoming bulk data packet.
		
		memset(BulkBuffer, '\0', sizeof(BulkBuffer));
		
		
		Endpoint_Read_Stream_LE(BulkBuffer, sizeof(BulkBuffer), &BulkBufferData);
		
		// Acknowledge the packet
		if (!Endpoint_IsReadWriteAllowed())
		{
			// ACK
			Endpoint_ClearOUT();
		}
		
		avrslcd_Clear();
		printf("%s", BulkBuffer);
		avrslcd_MoveCursor(2,1);
		
		
		//Reverse the data
		for (int i = 0; i < ((BulkBufferData-1)/2); i++)
		{
			char temp = BulkBuffer[i];
			BulkBuffer[i] = BulkBuffer[BulkBufferData - (i+2)];
			BulkBuffer[BulkBufferData - (i+2)] = temp;
		}
	
	}	
	
	// Bulk data out
	Endpoint_SelectEndpoint(BULK_IN_EPNUM);
	
	// Test bulk function
	if(!Endpoint_IsConfigured() || !Endpoint_IsEnabled() || Endpoint_IsStalled())
	{
		FatalError("Endpoint not configured (bulk in).");
	}
	
	if (Endpoint_IsINReady())
	{
		uint16_t bytesProcessed = 0;
		// Send back some data
		Endpoint_Write_Stream_LE(BulkBuffer, BulkBufferData, &bytesProcessed);
		
		Endpoint_ClearIN();
	
		
		avrslcd_MoveCursor(2,1);
		printf("%s", BulkBuffer);
		
	}	
			
	// Restore endpoint
	Endpoint_SelectEndpoint(PrevEndpoint);
}

void ProcessVendorControlRequest()
{
	
	// Process incoming vendor control request
	switch(USB_ControlRequest.bRequest)
	{
		
		case COMMAND_Version:
		{
			
			Endpoint_ClearSETUP();	// ACK SETUP Packet.
			
			// Prepare Version Packet
			VersionCommand_t Buffer;
			GetVersionInformation(&Buffer);
			
			// Send version data to host
			Endpoint_Write_Control_Stream_LE(Buffer, sizeof(VersionCommand_t));
			Endpoint_ClearOUT();
			
			
		}
		break;
		
		
		case COMMAND_ESTOP:
		{
			// Act on the command without delay.
			ESTOP_Set();
			
			// Acknowledge the operation.
			Endpoint_ClearSETUP();	// ACK SETUP Packet.
			Endpoint_ClearStatusStage();	
			
		}			
		break;
					
		case COMMAND_JTAG:
		{
			
			Endpoint_ClearSETUP();	// ACK SETUP Packet.
			
			// Enter JTAG mode
			ESTOP_Set();
			JTAGChain_t* pDeviceChain = JTAG_Mode();
			
			if (pDeviceChain == NULL)
			{
				// Error STALL/NAK?
			} 
			else
			{
				
				// Provide the device chain details to the host
				Endpoint_Write_Control_Stream_LE(pDeviceChain, sizeof(JTAGChain_t) + (pDeviceChain->length * sizeof(JTAGDevice_t)));
				Endpoint_ClearOUT();
				
			}
			
			
			
		}			
		break;
	/*		
		case COMMAND_Reset:
		{	
			Endpoint_ClearSETUP();	// ACK SETUP Packet.
			unsigned char Buffer[16];
			Endpoint_Read_Control_Stream_LE(Buffer, 8);
			Endpoint_ClearIN();
			avrslcd_MoveCursor(2,1);
			printf("%s", Buffer);
		}
		break;
					
		case COMMAND_SAFE:
		{
			Endpoint_ClearSETUP();	// ACK SETUP Packet.
			wchar_t Buffer[8] = L"WHASUP?";
			Endpoint_Write_Control_Stream_LE(Buffer, 16);
			Endpoint_ClearOUT();
			avrslcd_MoveCursor(2,1);
			printf("4");
		}			
		break;
					
		case COMMAND_STOP:
			avrslcd_MoveCursor(2,1);
			printf("\"STOP\"");
		break;
					
		case COMMAND_START:
			avrslcd_MoveCursor(2,1);
			printf("\"START\"");
		break;
	*/
		default:
			avrslcd_MoveCursor(2,1);
			printf("Unknown Command");
		break;
	}
	
}

