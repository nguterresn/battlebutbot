#include "Robot.h"
#include <Arduino.h>
#include <EEPROM.h>
#include "MachineRoom.h"

extern settings_t robot_settings;

static void robot_update(settings_t* settings);
static void robot_load_configuration(void);
static int robot_get_battery(void);

/**
 * @brief Construct a new Robot:: Robot object
 *
 */
bool robot_init(void)
{
	if (!EEPROM.begin(EEPROM_SIZE)) {
		return false;
	}

	// Machine room should be called first.
	machine_room_init();
	// Load the configuration as soon as the robot boots.
	robot_load_configuration();

	return true;
}

static void robot_update(settings_t* settings)
{
	memcpy(&robot_settings, settings, sizeof(settings_t));
	machine_room_change(settings);
}

/**
 * @brief Save new configuration on the EEPROM
 *
 * @param configuration as an integer
 * @param speed as an integer
 * @param friction as an integer
 */
void robot_save_configuration(int configuration, int speed, int drift)
{
	// Confirm all of them are the same and return.
	if (robot_settings.configuration == configuration &&
	    robot_settings.speed &&
	    robot_settings.drift == drift) {
		return;
	}
	configuration &= 0xff;
	speed         &= 0xff;
	drift         &= 0xff;

	// Save on EEPROM
	EEPROM.put(EEPROM_CONFIGURATION_INDEX, configuration);
	EEPROM.put(EEPROM_SPEED_INDEX, speed);
	EEPROM.put(EEPROM_DRIFT_INDEX, drift);
	EEPROM.commit();

	settings_t saved_settings = {
		.configuration = (uint8_t)configuration,
		.speed         = (uint8_t)speed,
		.drift         = (uint8_t)drift
	};

	// Save on RAM
	robot_update(&saved_settings);
}

/**
 * @brief Load configuration from EEPROM
 */
static void robot_load_configuration(void)
{
	uint8_t configuration         = EEPROM.read(EEPROM_CONFIGURATION_INDEX);
	uint8_t speed                 = EEPROM.read(EEPROM_SPEED_INDEX);
	uint8_t drift                 = EEPROM.read(EEPROM_DRIFT_INDEX);

	uint8_t configuration_default = CONFIGURATION_DEFAULT;
	uint8_t speed_default         = SPEED_DEFAULT;
	uint8_t drift_default         = DRIFT_DEFAULT;

	settings_t load_settings      = {
		.configuration = !configuration ? configuration_default : configuration,
		.speed         = !speed ? speed_default : speed,
		.drift         = !drift ? drift_default : drift
	};

	robot_update(&load_settings);
}

/**
 * @brief Method feedback when a client connects to the webpage
 */
void robot_connect(void)
{
	machine_room_reset();
}

void robot_flip(void)
{
	machine_room_flip();
}

/**
 * @brief Serializes the configuration, speed and mode into hex
 *
 * @param buffer of 10 bytes (set on `WebServer.cpp`)
 * @return int
 */
int robot_serialize_for_request(char* buffer)
{
	return sprintf(buffer,
	               "%02x%02x%02x%02x",
	               robot_settings.configuration,
	               robot_settings.speed,
	               robot_settings.drift,
	               robot_get_battery());
}

/**
 * @brief Returns battery level in percentage based on a 10-bit ADC read.
 *
 * @return uint8_t as the battery level (0-100)
 */
static int robot_get_battery(void)
{
	int digitalValueRead = analogRead(BATTERY_SENSOR);

	int level            = 0.3417 * digitalValueRead - 250;

	if (level < 0) {
		return 0;
	}
	return level;
}
