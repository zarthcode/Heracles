/*
 * Configuration.h
 *
 * Created: 9/12/2012 11:39:42 PM
 *  Author: Anthony
 */ 

#pragma once

#include <stdbool.h>


/// The maximum number of A3988 motor bridges available
#define MAX_CHANNELS 20

/// The maximum number of encoders
#define MAX_ENCODERS 10

/// The maximum number of switches
#define MAX_SWITCHES 10


/// Supported Channel/Device Types
typedef enum
{
		
	CH_DISABLED,	// Not assigned to a logical channel
	CH_DC,		// DC Motor Mode (req 1 ch.)
	CH_SERVO,	// Servo Mode (req 1 ch + encoder)
	CH_STEPPER,	// Stepper Mode - req 2 ch., optional encoder
	CH_BLDC,		// BLDC Mode - req 3 ch + optional encoders/sensors (3 hall + 1 other)
		
} ChannelTypes_t;
	
// Encoder Type
typedef enum
{
	
	ENCODER_NONE,
	ENCODER_HALL,		// Hall Effect (ADC/Analog)
	ENCODER_ABSOLUTE,	// Absolute encoder Digital
	ENCODER_INCREMENTAL	// Incremental encoder
		
} EncoderType_t;
	
/// Encoder Configuration
/// \todo Configurable GPIO
typedef struct
{
		
	unsigned char ID,				// Encoder ID
	unsigned char Channel,			// Device/Channel assignment
	EncoderType_t Type,				// Encoder Type, NONE if disabled
	uint32_t Resolution,			// Resolution
	uint32_t Accuracy,				// Accuracy, in counts
	uint32_t CPR,					// Counts per revolution
	bool bIndex,			// Indicates the presence of an index
	bool bPersistence		// Persistence (Store last known position/count)
	
} EncoderConfig_t;
	
	
	
/// Limit Switch Type	
/// Indicates if the switch is a limit or homing switch
typedef enum
{
	
	SWITCH_NONE,
	SWITCH_LIMIT,
	SWITCH_HOME
		
} SwitchType_t;
	
/// Indicates the location of the limit switch along the axis
typedef enum
{
		
	NEGATIVE,
	POSITIVE
		
} Direction_t;
	
/// Indicates whether the switch is normally open or closed
typedef enum
{
	SW_NORMALLYOPEN,
	SW_NORMALLYCLOSED
} SwitchState_t;
	
/// Limit switch configuration
/// \todo Configurable GPIO
typedef struct
{
		
	unsigned char SwitchID,		/// Address of the switch
	unsigned char Channel,		/// Logical Channel this switch is assigned to.
	SwitchType_t Type,			/// Type of switch
	Direction_t Direction,		/// Position of the switch
	SwitchState_t NormalState	/// Indicates NO/NC type
									
} LimitSwitch_t;
	
/// Velocity & Acceleration limits
typedef struct
{
	
	uint32_t Velocity,		// Velocity Limits
	uint32_t Acceleration,	// Acceleration Limits
	
} Limits_t;
	
/// Channel information
/// A logical channel represents one device (stepper, dc motor, bldc, etc.)
/// Each logical channel can utilize multiple bridges
typedef struct
{
	uint8_t Number,				// Channel number
	ChannelTypes_t Type,		// Type of motor channel
	Limits_t Limits,		// Velocity and acceleration limits for this channel.
		
	EncoderConfig_t* Encoders[4],		// Encoders associated with this channel (4 Max)
		
	Bridge_t* Bridges[3],			// Listing of Bridges this channel is mapped to. (3 Max)
	LimitSwitch_t* Switches[3],		// Homing and limit SwitchIDs this channel is associated with. (3 Max)
		
} Channel_t;
	
/// Bridge Assignment
/// Associates a bridge to a logical/motor/device.
typedef struct
{
		
	Channel_t* Channel,		/// Assigned logical device channel/parent
		
} Bridge_t;



/// Clears all device configuration data
void ClearConfiguration();

/// Loads Configuration Data from EEPROM
void LoadConfiguration();

/// Saves Configuration Data to EEPROM
void SaveConfiguration();

/// Configures a Channel
void ConfigureChannel( uint8_t chNum, ChannelTypes_t chType, VectorLimits Limits);

/// Configures a limit switch
void ConfigureSwitch( uint8_t SwitchID, uint8_t chNum, SwitchState_t Type, Direction_t Direction, SwitchState_t NormalState );

/// Configure an encoder
void ConfigureEncoder( uint8_t EncoderID, uint8_t chNum, EncoderType_t Type, uint32_t Resolution, uint32_t Accuracy, uint32_t CPR, bool bIndex, bool bPersistence );

/// Configures Hall encoders for a BLDC channel
void ConfigureHall( uint8_t chNum, uint8_t HallA, uint8_t HallB, uint8_t HallC);

/// Configures a stepper motor
void ConfigureStepper( uint8_t chNum, uint8_t BridgeA, uint8_t BridgeB);

/// Configures a DC motor
void ConfigureDC( uint8_t chNum, uint8_t Bridge);

/// Configures a BLDC motor
void ConfigureBLDC( uint8_t chNum, uint8_t BridgeU, uint8_t BridgeV, uint8_t BridgeW);

/// Configure a PID Controller
void ConfigurePID( uint8_t chNum, int32_t Kp, int32_t Ki, int32_t Kd);

/// Configure a secondary (outer-loop) PID Controller
void ConfigurePID2( uint8_t chNum, int32_t Kp, int32_t Ki, int32_t Kd);