/*
 * Descriptors.c
 *
 * Created: 8/5/2012 9:12:47 PM
 *  Author: Anthony
 */ 

#include "Descriptors.h"
#include "Endpoints.h"



const USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor =
{
	.Config =
	{
	.Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},

	.TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
	.TotalInterfaces        = 1,

	.ConfigurationNumber    = 1,
	.ConfigurationStrIndex  = NO_DESCRIPTOR,

	.ConfigAttributes       = USB_CONFIG_ATTR_RESERVED|USB_CONFIG_ATTR_SELFPOWERED|USB_CONFIG_ATTR_REMOTEWAKEUP,

	.MaxPowerConsumption    = USB_CONFIG_POWER_MA(100)
},

.Interface =
{
.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

.InterfaceNumber        = 0,
.AlternateSetting       = 0,
.TotalEndpoints         = 6,

.Class                  = 0xFF,
.SubClass               = 0xAA,
.Protocol               = 0x00,

.InterfaceStrIndex      = NO_DESCRIPTOR
	},

	.DataInEndpoint =
	{
		 .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

		 .EndpointAddress        = (ENDPOINT_DIR_IN | BULK_IN_EPNUM),
		 .Attributes             = EP_TYPE_BULK,
		 .EndpointSize           = BULK_IN_EPSIZE,
		 .PollingIntervalMS      = 0x00
	},

	.DataOutEndpoint =
	 {
		.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

		.EndpointAddress        = (ENDPOINT_DIR_OUT | BULK_OUT_EPNUM),
		.Attributes             = EP_TYPE_BULK,
		.EndpointSize           = BULK_OUT_EPSIZE,
		.PollingIntervalMS      = 0x00
	},


	.InterruptOutEndpoint =
	{
		.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

		.EndpointAddress        = (ENDPOINT_DIR_OUT | INTERRUPT_OUT_EPNUM),
		.Attributes             = EP_TYPE_INTERRUPT,
		.EndpointSize           = INTERRUPT_OUT_EPSIZE,
		.PollingIntervalMS      = 0x32
	},

	.InterruptInEndpoint =
	{
		.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

		.EndpointAddress        = (ENDPOINT_DIR_IN | INTERRUPT_IN_EPNUM),
		.Attributes             = EP_TYPE_INTERRUPT,
		.EndpointSize           = INTERRUPT_IN_EPSIZE,
		.PollingIntervalMS      = 0x32
	},
	
	.IsochronousOutEndpoint =
	{
		.Header					= {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},
		
		.EndpointAddress		= (ENDPOINT_DIR_OUT | ISOCHRONOUS_OUT_EPNUM),
		.Attributes				= EP_TYPE_ISOCHRONOUS,
		.EndpointSize			= ISOCHRONOUS_OUT_EPSIZE,
		.PollingIntervalMS		= 0x00
	},	
	
	.IsochronousInEndpoint =
	{
		.Header					= {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},
	
		.EndpointAddress		= (ENDPOINT_DIR_IN | ISOCHRONOUS_IN_EPNUM),
		.Attributes				= EP_TYPE_ISOCHRONOUS,
		.EndpointSize			= ISOCHRONOUS_IN_EPSIZE,
		.PollingIntervalMS		= 0x00
	}	


};

uint16_t CALLBACK_USB_GetDescriptor( const uint16_t wValue, const uint8_t wIndex, const void** const DescriptorAddress)
{
	const uint8_t  DescriptorType   = (wValue >> 8);
	const uint8_t  DescriptorNumber = (wValue & 0xFF);

	void*    Address = NULL;
	uint16_t Size    = NO_DESCRIPTOR;

	switch (DescriptorType) {
		case DTYPE_Device:
			Address = (void*)&DeviceDescriptor;
			Size    = sizeof(USB_Descriptor_Device_t);
		break;
		case DTYPE_Configuration:
			Address = (void*)&ConfigurationDescriptor;
			Size    = sizeof(USB_Descriptor_Configuration_t);
		break;
		case DTYPE_String:
	
			switch (DescriptorNumber)
			{
			
				case 0x00:
					Address = (void*)&LanguageString;
					Size    = pgm_read_byte(&LanguageString.Header.Size);
				break;
				case 0x01:
					Address = (void*)&ManufacturerString;
					Size    = pgm_read_byte(&ManufacturerString.Header.Size);
				break;
				case 0x02:
					Address = (void*)&ProductString;
					Size    = pgm_read_byte(&ProductString.Header.Size);
				break;
				case 0x03:
					Address = (void*)&DeviceSerialString;
					Size    = pgm_read_byte(&DeviceSerialString.Header.Size);
				break;
				
				
			}
			
		break;
	}

	*DescriptorAddress = Address;
	return Size;
}
