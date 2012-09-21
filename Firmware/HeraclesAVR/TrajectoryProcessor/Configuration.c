/*
 * Configuration.c
 *
 * Created: 9/13/2012 1:09:16 AM
 *  Author: Anthony
 */ 

#include "Configuration.h"
#include <avr/eeprom.h>


/// Number of Logical Devices in use
static int NumChannels = 0;

/// Array containing Device/Channel descriptions
static Channel_t DeviceChannels[MAX_CHANNELS];

/// Array containing Device/Channel descriptions (EEPROM)
static Channel_t EEMEM EE_DeviceChannels[MAX_CHANNELS];


/// Limit switches
static LimitSwitch_t LimitSwitches[MAX_SWITCHES];

/// Limit switches (EEPROM)
static LimitSwitch_t EEMEM EE_LimitSwitches[MAX_SWITCHES];

/// Motor Bridges
static Bridge_t Bridges[MAX_CHANNELS];

/// Motor Bridges (EEPROM)
static Bridge_t EEMEM EE_Bridges[MAX_CHANNELS];

/// Encoders
static EncoderConfig_t Encoders[MAX_ENCODERS];

/// Encoders (EEPROM)
static EncoderConfig_t EEMEM EE_Encoders[MAX_ENCODERS];


void ClearConfiguration()
{
	// Trajectory processor must be offline (configuration write)
	
	// Clear all channels
	for (int i = 0; i < MAX_CHANNELS; i++)
	{
		DeviceChannels[i]->Number = i;
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
	
		DeviceChannels[i]->Limits.Velocity = 0;
		DeviceChannels[i]->Limits.Acceleration = 0;
	
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
	
	// Read configuration from EEPROM
	eeprom_read_block((void*)&DeviceChannels, (void*)&EE_DeviceChannels, sizeof DeviceChannels);
	eeprom_read_block((void*)&LimitSwitches, (void*)&EE_LimitSwitches, sizeof LimitSwitches);
	eeprom_read_block((void*)&Encoders, (void*)&EE_Encoders, sizeof Encoders);
	eeprom_read_block((void*)&Bridges, (void*)EE_Bridges, sizeof Bridges);

}

void SaveConfiguration()
{
	
	// Write configuration to EEPROM
	eeprom_write_block((void*)&DeviceChannels, (void*)&EE_DeviceChannels, sizeof DeviceChannels);
	eeprom_write_block((void*)&LimitSwitches, (void*)&EE_LimitSwitches, sizeof LimitSwitches);
	eeprom_write_block((void*)&Encoders, (void*)&EE_Encoders, sizeof Encoders);
	eeprom_write_block((void*)&Bridges, (void*)EE_Bridges, sizeof Bridges);

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
	
	DeviceChannels[chNum]->Bridges[0] = NULL;
	DeviceChannels[chNum]->Bridges[1] = NULL;
	DeviceChannels[chNum]->Bridges[2] = NULL;
	
	DeviceChannels[chNum]->Switches[0] = NULL;
	DeviceChannels[chNum]->Switches[1] = NULL;
	DeviceChannels[chNum]->Switches[2] = NULL;
	
	DeviceChannels[chNum]->Encoders[0] = NULL;
	DeviceChannels[chNum]->Encoders[1] = NULL;
	DeviceChannels[chNum]->Encoders[2] = NULL;
	DeviceChannels[chNum]->Encoders[3] = NULL;
	
	
	// Configure channel
	DeviceChannels[chNum]->Type = chType;
	DeviceChannels[chNum]->Limits = Limits;
	

}

void ConfigureSwitch( uint8_t SwitchID, uint8_t chNum, SwitchState_t Type, Direction_t Direction, SwitchState_t NormalState )
{
	
	// Set switch properties
	LimitSwitches[SwitchID]->Channel = chNum;
	LimitSwitches[SwitchID]->Type = Type;
	LimitSwitches[SwitchID]->Direction = Direction;
	LimitSwitches[SwitchID]->NormalState = NormalState;

	uint8_t switchIndex = 0;

	// 0 - Negative Limit
	// 1 - Positive Limit
	// 2 - Home switch
	switch (Type)
	{
	case SWITCH_LIMIT:
		
		switch (Direction)
		{
			case NEGATIVE:
				switchIndex = 0;
				break;
			case POSITIVE:
				switchIndex = 1;
				break;
			default:
				// Error
				return;
				break;
		}
		break;
	case SWITCH_HOME:
		switchIndex = 2;
		break;
	default:
		// Error
		return;
		break;
	}

	// Set forward pointer
	DeviceChannels[chNum]->Switches[switchIndex] = &LimitSwitches[SwitchID];
	

}

void ConfigureEncoder( uint8_t EncoderID, uint8_t chNum, EncoderType_t Type, uint32_t Resolution, uint32_t Accuracy, uint32_t CPR, bool bIndex, bool bPersistence )
{
	
	DeviceChannels[chNum]->Encoders[0] = &Encoders[EncoderID];
	
	Encoders[EncoderID]->Channel = chNum;
	Encoders[EncoderID]->Type = Type;
	Encoders[EncoderID]->ID = 0;
	Encoders[EncoderID]->Resolution = Resolution;
	Encoders[EncoderID]->Accuracy = Accuracy;
	Encoders[EncoderID]->CPR = CPR;
	Encoders[EncoderID]->bIndex = bIndex;
	Encoders[EncoderID]->bPersistence = bPersistence;

}

void ConfigureStepper( uint8_t chNum, uint8_t BridgeA, uint8_t BridgeB )
{
	
	// Assign bridges
	Bridges[BridgeA]->Channel = &DeviceChannels[chNum];
	Bridges[BridgeB]->Channel = &DeviceChannels[chNum];
	
	DeviceChannels[chNum]->Bridges[0] = &Bridges[BridgeA];
	DeviceChannels[chNum]->Bridges[1] = &Bridges[BridgeB];
	DeviceChannels[chNum]->Bridges[2] = NULL;
	
}

void ConfigureDC( uint8_t chNum, uint8_t Bridge )
{
	
	Bridges[BridgeB]->Channel = &DeviceChannels[chNum];
	
	DeviceChannels[chNum]->Bridges[0] = &Bridges[Bridge];
	DeviceChannels[chNum]->Bridges[1] = NULL;
	DeviceChannels[chNum]->Bridges[2] = NULL;
}

void ConfigureBLDC( uint8_t chNum, uint8_t BridgeU, uint8_t BridgeV, uint8_t BridgeW )
{
	
	Bridges[BridgeU]->Channel = &DeviceChannels[chNum];
	Bridges[BridgeV]->Channel = &DeviceChannels[chNum];
	Bridges[BridgeW]->Channel = &DeviceChannels[chNum];
	
	DeviceChannels[chNum]->Bridges[0] = &Bridges[BridgeU];
	DeviceChannels[chNum]->Bridges[1] = &Bridges[BridgeV];
	DeviceChannels[chNum]->Bridges[2] = &Bridges[BridgeW];
}

