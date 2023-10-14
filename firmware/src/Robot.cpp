#include "Robot.h"
#include "EEPROM.h"

MachineRoom oMachineRoom;
static uint8_t robot_configuration, robot_speed;

/**
 * @brief Construct a new Robot:: Robot object
 *
 */
void robot_init(void)
{
	EEPROM.begin(CONFIGURATION_SIZE);

	// Load the configuration as soon as the robot boots.
	robot_load_configuration();
}

void robot_update(int configuration, int speed)
{
	oMachineRoom.change(configuration, configuration);

	robot_configuration = configuration;
	robot_speed         = speed;
}

/**
 * @brief Method feedback when a client connects to the webpage
 *
 */
void robot_connect(void)
{
	oMachineRoom.reset();
}

/**
 * @brief Save new configuration on the EEPROM
 *
 * @param configuration as a byte
 * @param speed as a byte
 * @param friction as a byte
 */
void robot_save_configuration(int configuration, int speed)
{
	// Confirm all of them are the same and return.
	if (robot_configuration == configuration && robot_speed == speed) {
		return;
	}
	// Save on EEPROM
	EEPROM.put(CONFIGURATION, configuration);
	EEPROM.put(SPEED, speed);
	EEPROM.commit();
	// Save on RAM
	robot_configuration = configuration;
	robot_speed         = speed;

	robot_update(robot_configuration, robot_speed);
}

/**
 * @brief Load configuration from EEPROM
 *
 */
void robot_load_configuration(void)
{
	uint8_t configuration = EEPROM.read(CONFIGURATION);
	uint8_t eepromSpeed   = EEPROM.read(SPEED);

	robot_configuration = !configuration ? CONFIGURATION_DEFAULT : configuration;
	robot_speed         = !eepromSpeed ? SPEED_DEFAULT : eepromSpeed;

	robot_update(robot_configuration, robot_speed);
}

/**
 * @brief Returns battery level in percentage based on a 10-bit ADC read.
 *
 * @return uint8_t as the battery level (0-100)
 */
int robot_get_battery(void)
{
	int digitalValueRead = analogRead(BATTERY_SENSOR);

	int level            = 0.3417 * digitalValueRead - 250;

	if (level < 0) {
		return 0;
	}
	return level;
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
	               "%02x%02x%02x",
	               robot_configuration,
	               robot_speed,
	               robot_get_battery());
}
