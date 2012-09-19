/*
 * Version.c
 *
 * Created: 9/12/2012 1:11:32 AM
 *  Author: Anthony
 */ 

#include "USBCommand.h"

#include "Version.h"


void GetVersionInformation( VersionCommand_t* pVersionCommand )
{
	/// \todo Implement GetVersionInformation

	pVersionCommand->major = VERSION_MAJOR;
	pVersionCommand->minor = VERSION_MINOR;
	pVersionCommand->milli = VERSION_MILLI;
	
	pVersionCommand->build = VERSION_BUILD_NUMBER;
			

}
