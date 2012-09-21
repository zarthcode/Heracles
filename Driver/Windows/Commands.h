// Heracles USB Commands

/// \todo Maybe this file should be synced externally?

typedef enum 
{

	COMMAND_Version,	// Retrieves Protocol/Version Information
	COMMAND_ESTOP,		// Sets an ESTOP condition
	COMMAND_Config,		// Performs device configuration
	COMMAND_JTAG,		// Enables JTAG programming mode
	COMMAND_Mode,		// 
	COMMAND_Status		// Returns device status.

} CommandID_t;


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


// JTAG commands

// DFU Command

// Device Configuration
// Configuration Modes
typedef enum
{
	CONFIG_CLEAR,	// Clear device configuration
	CONFIG_READ,	// Read configuration
	CONFIG_WRITE	// Write configuration
} ConfigurationMode_t;