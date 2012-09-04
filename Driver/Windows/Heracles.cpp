#pragma once

#include "Heracles.h"
#include <boost/smart_ptr.hpp>
#include <string>


libusb_context* Heracles::libusbContext = nullptr;
unsigned int Heracles::deviceCount = 0;


libusb_context* Heracles::getContext()const
{
	return libusbContext;	
}

Heracles::Heracles()
{
	// Increment the deviceCount
	deviceCount++;

	if (libusbContext == nullptr)
	{
		int Result = libusb_init(&libusbContext);

		if (Result != LIBUSB_SUCCESS)
		{
			/// \todo Add libusbTranslateResult() here.
			throw std::exception("libusb_init() failed.");
		}
	}

	shared_ptr<libusb_context> pContext();
}

Heracles::~Heracles()
{

	if (--deviceCount == 0)
	{
		// Close libusb
		libusb_exit(libusbContext);
	}
}

void Heracles::Open()
{

	// Get a list of libusb devices
	libusb_device** deviceList;
	int Result = libusb_get_device_list(getContext(), &deviceList);

	// Locate a suitable heracles device


}


