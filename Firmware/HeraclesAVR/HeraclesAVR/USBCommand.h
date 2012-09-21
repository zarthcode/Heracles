/*
 * USBCommand.h
 *
 * Created: 8/8/2012 12:34:29 AM
 *  Author: Anthony
 */ 

#pragma once
#include <stdbool.h>

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
			CONFIG_LOAD,	// Read configuration from EEPROM
			CONFIG_SAVE,	// Write configuration to EEPROM
			CONFIG_CHANNEL,	// Inits/Configures a motor channel
			CONFIG_SWITCH,	// Configures a limit/homing switch
			CONFIG_ENCODER,
			CONFIG_HALL,
			CONFIG_STEPPER,
			CONFIG_DC,
			CONFIG_BLDC
			
		} ConfigurationCommands_t;
	
	
		// Configuration Commands
		
		// Configure Channel
		typedef struct
		{
			uint8_t ChannelNumber;
			ChannelTypes_t Type;
			uint32_t VelocityLimit;
			uint32_t AccelerationLimit;
			
		} CMDConfigureChannel_t;
		
		// Configure Switch
		typedef struct
		{
			
			uint8_t SwitchID;
			uint8_t ChannelNumber;
			SwitchState_t Type;
			Direction_t Direction;
			SwitchState_t NormalState;
			
		} CMDConfigureSwitch_t;
		
		// Configure Encoder
		typedef struct
		{
			
			uint8_t EncoderID;
			uint8_t ChannelNumber;
			EncoderType_t Type;
			uint32_t Resolution;
			uint32_t Accuracy;
			uint32_t CPR;
			bool bIndex;
			bool bPersistence;
			
		} CMDConfigureEncoder_t;
		
		// Configure Hall
		typedef struct
		{
			
			uint8_t ChannelNumber;
			uint8_t HallA;
			uint8_t HallB;
			uint8_t HallC;
			
		} CMDConfigureHall_t;
		
		// Configure Stepper
		typedef struct
		{
			
			uint8_t ChannelNumber;
			uint8_t BridgeA;
			uint8_t BridgeB;
			
		} CMDConfigureStepper_t;
		
		// Configure DC
		typedef struct
		{
			
			uint8_t ChannelNumber;
			uint8_t BridgeA;
			
		} CMDConfigureDC_t;
		
		// Configure BLDC
		typedef struct
		{
			
			uint8_t ChannelNumber;
			uint8_t BridgeA;
			uint8_t BridgeB;
			uint8_t BridgeC;
			
		} CMDConfigureBLDC_t;
		
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
			
		