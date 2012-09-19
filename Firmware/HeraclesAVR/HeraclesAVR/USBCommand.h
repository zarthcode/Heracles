/*
 * USBCommand.h
 *
 * Created: 8/8/2012 12:34:29 AM
 *  Author: Anthony
 */ 

#pragma once

/// Heracles commands
typedef enum
{
	COMMAND_Version,	// Retrieves Protocol/Version Information
	COMMAND_ESTOP,		// Sets an ESTOP condition
	COMMAND_Config,		// Performs device configuration
	COMMAND_JTAG,		// Enables JTAG programming mode
	COMMAND_Mode,		// Enables interactive/direct-control mode
	COMMAND_Status		// Returns device status.
	
} CommandID_t;



// Commands
	
	// Version Command
	typedef struct  
	{
		
		// Firmware Information
	
		unsigned char major;	// Major features
		unsigned char minor;	// Minor features, major fixes
		unsigned char milli;	// Minor Fixes
		
		unsigned int build;		// Build number
		
		// Hardware Information
	
		unsigned int HWRevision;
			
		
	} VersionCommand_t;
	
	// ESTOP Control Command
		// [No parameters]
	
	
	// JTAG Mode - Directly program jtag devices (MCU and CPLD)
	typedef struct
	{
		JTAGState_t state;
		size_t DataLength;	// Data Length
		
		// Data
		unsigned char Data*;
		
	} JTAGCommand_t;
	
	/// JTAG return packet
	typedef struct  
	{
		JTAGError_t code;
		size_t DataLength;
		
		// Data
		unsigned char Data*;
	} JTAGStatus_t;
			
	
	
	// DFU Startup flag
		
		
	// Device Configuration
	
		// Configuration Modes
		typedef enum
		{
			CONFIG_CLEAR,	// Clear device configuration
			CONFIG_READ,	// Read configuration
			CONFIG_WRITE	// Write configuration
		} ConfigurationMode_t;
	
	
		
	// Command Mode - Send commands to secondary MCU (Motion Planner)
		
		// Open Loop Speed Mode
		
		
		// Closed Loop Speed Mode
		
		// Closed Loop Position Mode
		
		// Open Loop Position Mode
	
	// Positioning commands
	
		// Set velocity
		// Set position
		
			// Acceleration
			// Speed
			// Deacceleration
			
		