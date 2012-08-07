/*
 * Descriptors.c
 *
 * Created: 8/5/2012 9:12:47 PM
 *  Author: Anthony
 */ 

#include "Descriptors.h"
#include "Endpoints.h"


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
				
			}
			
		break;
	}

	*DescriptorAddress = Address;
	return Size;
}
