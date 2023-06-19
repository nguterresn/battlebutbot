// Fields inside the configuration
#define ENABLE_CONSOLE_TEXT 0x01
#define ENABLE_FEEDBACK_LED 0x02
#define ENABLE_SERVO        0x04
#define TOGGLE_MODE         0x08

// Fields to exchange with the webpage and save on the EEPROM
typedef enum {
	CONFIGURATION,
	SPEED,
	CONFIGURATION_SIZE
} configuration;
