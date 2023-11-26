#ifndef CONFIG_FIELDS_H_
#define CONFIG_FIELDS_H_

// Fields inside the configuration
#define ENABLE_FEEDBACK_LED        0x01 // Disabled / Enabled
#define ENABLE_SERVO               0x02 // Disabled / Enabled
#define ENABLE_AUTO_MODE           0x04 // Manual / Automatic

#define CONFIGURATION_DEFAULT      ENABLE_FEEDBACK_LED | ENABLE_SERVO

#define EEPROM_CONFIGURATION_INDEX 0x00
#define EEPROM_SPEED_INDEX         0x04
#define EEPROM_DRIFT_INDEX         0x08
#define EEPROM_SIZE                12  // In bytes

typedef enum {
	MANUAL,
	AUTO
} RobotMode;

#endif /* CONFIG_FIELDS_H_ */
