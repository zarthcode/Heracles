/*
 * Configuration.c
 *
 * Created: 9/13/2012 1:09:16 AM
 *  Author: Anthony
 */ 

#include "Configuration.h"



/// Number of Logical Devices in use
static int NumChannels = 0;

/// Array containing Device/Channel descriptions
static Channel_t DeviceChannels[MAX_CHANNELS];



/// Limit switches
static LimitSwitch_t LimitSwitches[MAX_SWITCHES];

/// Motor Bridges
static Bridge_t Bridges[MAX_CHANNELS];

/// Encoders
static EncoderConfig_t Encoders[MAX_ENCODERS];


void ClearConfiguration()
{
	// Trajectory processor must be offline (configuration write)
	
	// Clear all channels
	for (int i = 0; i < MAX_CHANNELS; i++)
	{
		DeviceChannels[i]->Type = ChannelTypes_t.CH_DISABLED;
		
		DeviceChannels[i]->Encoders[0] = NULL;
		DeviceChannels[i]->Encoders[1] = NULL;
		DeviceChannels[i]->Encoders[2] = NULL;
		DeviceChannels[i]->Encoders[3] = NULL;
		
		DeviceChannels[i]->Bridges[0] = NULL;
		DeviceChannels[i]->Bridges[1] = NULL;
		DeviceChannels[i]->Bridges[2] = NULL;
		
		DeviceChannels[i]->Switches[0] = NULL;
		DeviceChannels[i]->Switches[1] = NULL;
		DeviceChannels[i]->Switches[2] = NULL;
	
	
	// Remove configured bridges
	
		Bridges[i]->Channel = 0;
		
	}

	
	// Remove configured switches	
	for(int i = 0; i < MAX_SWITCHES; i++)	
	{
		LimitSwitches[i]->Channel = 0;
		LimitSwitches[i]->SwitchID = 0;
		LimitSwitches[i]->Type = SwitchType_t.SWITCH_LIMIT;
	}
	
	
	// remove configured encoders
	for(int i = 0; i < MAX_ENCODERS; i++)
	{
		
		Encoders[i]->Type = ENCODER_NONE;
		Encoders[i]->Channel = 0;
		Encoders[i]->ID = 0;
		Encoders[i]->Accuracy = 0;
		Encoders[i]->bIndex = 0;
		Encoders[i]->CPR = 0;
		Encoders[i]->Resolution = 0;
		
	}
	
}

void LoadConfiguration()
{
	
	/// \todo Implement LoadConfiguration
	

}

void SaveConfiguration()
{
	/// \todo Implement SaveConfiguration
	

}

void ConfigureChannel( uint8_t chNum, ChannelTypes_t chType, VectorLimits Limits)
{
	
	/// \todo Implement ConfigureChannel
	if (chNum > MAX_CHANNELS)
	{
		// Invalid configuration
		return;
	}
	
	// Validate configuration
	
	// Clear channel
	
	// Configure channel
	DeviceChannels[chNum]->Type = chType;
	DeviceChannels[chNum]->Limits = Limits;
	

}

void ConfigureSwitch( uint8_t SwitchID, uint8_t chNum, SwitchState_t Type, Direction_t Direction, SwitchState_t NormalState )
{
	
	LimitSwitches[SwitchID]

}

void ConfigureEncoder( EncoderConfig_t* pEncoder )
{
	
	Encoders[i]->Channel = 0;
	Encoders[i]->Type = ENCODER_NONE;
	Encoders[i]->ID = 0;
	Encoders[i]->Resolution = 0;
	Encoders[i]->Accuracy = 0;
	Encoders[i]->CPR = 0;
	Encoders[i]->bIndex = 0;
	Encoders[i]->bPersistence = 0;

}

