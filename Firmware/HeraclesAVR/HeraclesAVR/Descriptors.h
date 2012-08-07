/*
 * Descriptors.h
 *
 * Created: 8/5/2012 3:36:25 PM
 *  Author: Anthony
 */ 
#pragma once

#include <stdint.h>
#include <avr/pgmspace.h>
#include "LUFA/Drivers/USB/USB.h"


const USB_Descriptor_Device_t PROGMEM DeviceDescriptor =
{
	.Header					= { .Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},
	
	.USBSpecification		= VERSION_BCD(01.10),
	.Class					= 0xFF,
	.SubClass				= 0xAA,
	.Protocol				= 0x00,
	
	.Endpoint0Size			= FIXED_CONTROL_ENDPOINT_SIZE,
	
	.VendorID				= 0x0000,
	.ProductID				= 0x0000,
	.ReleaseNumber			= VERSION_BCD(00.01),
	
	.ManufacturerStrIndex	= 0x01,
	.ProductStrIndex		= 0x02,
	.SerialNumStrIndex		= USE_INTERNAL_SERIAL,
	
	.NumberOfConfigurations	= FIXED_NUM_CONFIGURATIONS
	
};

const USB_Descriptor_String_t PROGMEM LanguageString =
{
	.Header					= {.Size = USB_STRING_LEN(1), .Type = DTYPE_String},
	.UnicodeString			= {LANGUAGE_ID_ENG}
};

const USB_Descriptor_String_t PROGMEM ManufacturerString =
{
	.Header					= {.Size = USB_STRING_LEN(3), .Type = DTYPE_String},
	.UnicodeString			= L"ZarthCode LLC"
};

const USB_Descriptor_String_t PROGMEM ProductString =
{
 .Header                 = {.Size = USB_STRING_LEN(13), .Type = DTYPE_String},
 .UnicodeString          = L"Heracles Motion Controller"
};

uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
									const uint8_t wIndex,
									const void** const DescriptorAddress);