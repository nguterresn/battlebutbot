// Fields inside the configuration
#define ENABLE_FEEDBACK_LED   0x01 // Disabled / Enabled
#define ENABLE_SERVO          0x02 // Disabled / Enabled
#define ENABLE_AUTO_MODE      0x04 // Manual / Automatic

#define CONFIGURATION_DEFAULT ENABLE_FEEDBACK_LED | ENABLE_SERVO

// Fields to exchange with the webpage and save on the EEPROM
typedef enum {
	CONFIGURATION,
	SPEED,
	CONFIGURATION_SIZE
} configuration;

typedef enum {
	MANUAL,
	AUTO
} RobotMode;
