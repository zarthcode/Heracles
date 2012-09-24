/*
 * Version.h
 *
 * Created: 9/12/2012 1:11:16 AM
 *  Author: Anthony
 */ 

#pragma once


// Default build information
#ifndef VERSIONED_BUILD

	#define VERSION_MAJOR 0
	#define VERSION_MINOR 0
	#define VERSION_MILLI 0
	
	// Build number 0 ALWAYS denotes a developer/desk build. (Reserved for CI builds)
	#define VERSION_BUILD_NUMBER 0	
	
#endif


void GetVersionInformation(VersionCommand_t* pVersionCommand);

