/*
 * Endpoints.h
 *
 * Created: 8/5/2012 8:59:35 PM
 *  Author: Anthony
 */ 


#pragma once

#include "LUFA/Drivers/USB/USB.h"

#define BULK_OUT_EPSIZE			8
#define BULK_OUT_EPNUM			0x01

#define BULK_IN_EPSIZE			8
#define BULK_IN_EPNUM			0x02

#define INTERRUPT_OUT_EPSIZE	8
#define INTERRUPT_OUT_EPNUM		0x03

#define INTERRUPT_IN_EPSIZE		8
#define INTERRUPT_IN_EPNUM		0x04

#define COMMAND_EPSIZE			8
#define COMMAND_EPNUM			0x00



typedef struct
{
	USB_Descriptor_Configuration_Header_t Config;
	USB_Descriptor_Interface_t			Interface;
	USB_Descriptor_Endpoint_t			DataInEndpoint;			// Bulk data from the device
	USB_Descriptor_Endpoint_t			DataOutEndpoint;		// Bulk data to the device
	USB_Descriptor_Endpoint_t			InterruptOutEndpoint;	// Priority messages to the device
	USB_Descriptor_Endpoint_t			InterruptInEndpoint;	// Priority messages from the device
	USB_Descriptor_Endpoint_t			CommandEndpoint;		// IFP Firmware commands.
} USB_Descriptor_Configuration_t;

const USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor =
{
	.Config =
	{
		.Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},

		.TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
		.TotalInterfaces        = 1,

		.ConfigurationNumber    = 1,
		.ConfigurationStrIndex  = NO_DESCRIPTOR,

		.ConfigAttributes       = USB_CONFIG_ATTR_RESERVED,

		.MaxPowerConsumption    = USB_CONFIG_POWER_MA(100)
	},

	.Interface =
	{
		.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

		.InterfaceNumber        = 0,
		.AlternateSetting       = 0,
		.TotalEndpoints         = 5,

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
		.PollingIntervalMS      = 0x00
	},

	.InterruptInEndpoint =
	{
		.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

		.EndpointAddress        = (ENDPOINT_DIR_IN | INTERRUPT_IN_EPNUM),
		.Attributes             = EP_TYPE_INTERRUPT,
		.EndpointSize           = INTERRUPT_IN_EPSIZE,
		.PollingIntervalMS      = 0x00
	},


	.CommandEndpoint =
	{
		.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

		.EndpointAddress        = (ENDPOINT_DIR_OUT | COMMAND_EPNUM),
		.Attributes             = EP_TYPE_CONTROL,
		.EndpointSize           = COMMAND_EPSIZE,
		.PollingIntervalMS      = 0x00
	}

};