/*
 * Endpoints.h
 *
 * Created: 8/5/2012 8:59:35 PM
 *  Author: Anthony
 */ 
#pragma once

#include "LUFA/Drivers/USB/USB.h"


#define BULK_OUT_EPSIZE			8
#define BULK_OUT_EPNUM			0x04

#define BULK_IN_EPSIZE			8
#define BULK_IN_EPNUM			0x03

#define INTERRUPT_OUT_EPSIZE	8
#define INTERRUPT_OUT_EPNUM		0x01

#define INTERRUPT_IN_EPSIZE		8
#define INTERRUPT_IN_EPNUM		0x02


// Heracles Configuration Descriptor Structure

typedef struct
{
	USB_Descriptor_Configuration_Header_t Config;
	USB_Descriptor_Interface_t			Interface;
	USB_Descriptor_Endpoint_t			InterruptOutEndpoint;	// Priority messages to the device
	USB_Descriptor_Endpoint_t			InterruptInEndpoint;	// Priority messages from the device
	USB_Descriptor_Endpoint_t			DataInEndpoint;			// Bulk data from the device
	USB_Descriptor_Endpoint_t			DataOutEndpoint;		// Bulk data to the device
} USB_Descriptor_Configuration_t;

