/*
 * USBEvents.c
 *
 * Created: 8/19/2012 11:31:19 PM
 *  Author: Anthony
 */ 
#include <stdbool.h>

#include "global.h"
#include "Endpoints.h"
#include "USBImpl.h"
#include "LCD/avrslcd.h"

void EVENT_USB_Device_Connect(void)
{
	avrslcd_MoveCursor(1,1);
	printf("Connected");
}


void EVENT_USB_Device_ControlRequest(void)
{
	
	
	if((USB_ControlRequest.bmRequestType & ( /*CONTROL_REQTYPE_DIRECTION | */CONTROL_REQTYPE_TYPE)) == (/* REQDIR_HOSTTODEVICE | */ REQTYPE_VENDOR))
	{

		ProcessVendorControlRequest();
		
		// Clear the setup packet.
		
		
	}
	
	
	// Determine basic parameters
	// Type
	// uint8_t Type = bit_get(USB_ControlRequest.bmRequestType, CONTROL_REQTYPE_TYPE) >> 5;
	
	// Direction (false = OUT, true = IN)
	// bool bDirectionIN = bit_get(USB_ControlRequest.bmRequestType, CONTROL_REQTYPE_DIRECTION);
	
	// Recipient
	// uint8_t Recipient = bit_get(USB_ControlRequest.bmRequestType, CONTROL_REQTYPE_RECIPIENT);
	
//	avrslcd_Clear();
//	printf("Ctrl Rq %i", i++);
//	avrslcd_MoveCursor(2,1);
//	printf("R%i I%i V%i", USB_ControlRequest.bRequest, USB_ControlRequest.wIndex, USB_ControlRequest.wValue);
	
	

	// Vendor Specific
	
}


void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool success = true;
	
	// Configure the control endpoint
	// success &= Endpoint_ConfigureEndpoint(COMMAND_EPNUM, EP_TYPE_CONTROL, COMMAND_EPSIZE, 1);
	
	// Configure the bulk in endpoint
	success &= Endpoint_ConfigureEndpoint(ENDPOINT_DIR_OUT | BULK_OUT_EPNUM, EP_TYPE_BULK, BULK_OUT_EPSIZE, 1);
	
	// Configure the bulk OUT endpoint
	success &= Endpoint_ConfigureEndpoint(ENDPOINT_DIR_IN | BULK_IN_EPNUM, EP_TYPE_BULK, BULK_IN_EPSIZE, 1);
	
	// Configure the interrupt OUT endpoint
	success &= Endpoint_ConfigureEndpoint(INTERRUPT_OUT_EPNUM, EP_TYPE_INTERRUPT, INTERRUPT_OUT_EPSIZE, 1);
	
	// Configure the interrupt IN endpoint
	success &= Endpoint_ConfigureEndpoint(ENDPOINT_DIR_IN | INTERRUPT_IN_EPNUM, EP_TYPE_INTERRUPT, INTERRUPT_IN_EPSIZE, 1);
	
	// Configure the isochronous OUT endpoint
	success &= Endpoint_ConfigureEndpoint(ISOCHRONOUS_OUT_EPNUM, EP_TYPE_ISOCHRONOUS, ISOCHRONOUS_OUT_EPSIZE, 1);
	
	// Configure the isochronous IN endpoint
	success &= Endpoint_ConfigureEndpoint(ENDPOINT_DIR_IN | ISOCHRONOUS_IN_EPNUM, EP_TYPE_ISOCHRONOUS, ISOCHRONOUS_IN_EPSIZE, 1);
	
	avrslcd_MoveCursor(1,1);
	printf("Configured");
}

