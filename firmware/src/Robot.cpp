#include "Robot.h"

/**
 * @brief Construct a new Robot:: Robot object
 *
 */
Robot::Robot() : oMachineRoom()
{
	EEPROM.begin(CONFIGURATION_SIZE);

	// Load the configuration as soon as the robot boots.
	loadConfiguration();
}

/**
 * @brief Update capabilities according to the configuration saved on the EEPROM.
 *
 */
void Robot::update(void)
{
	oMachineRoom.change(this->configuration);
	oMachineRoom.changeSpeed(this->speed);
}

/**
 * @brief Method feedback when a client connects to the webpage
 *
 */
void Robot::connect(void)
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
void Robot::saveConfiguration(int configuration, int speed)
{
	// Confirm all of them are the same and return.
	if (this->configuration == configuration && this->speed == speed) {
		return;
	}
	// Save on EEPROM
	EEPROM.put(CONFIGURATION, configuration);
	EEPROM.put(SPEED, speed);
	EEPROM.commit();
	// Save on RAM
	this->configuration = configuration;
	this->speed         = speed;

	update();
}

/**
 * @brief Load configuration from EEPROM
 *
 */
void Robot::loadConfiguration(void)
{
	uint8_t configuration = EEPROM.read(CONFIGURATION);
	uint8_t eepromSpeed   = EEPROM.read(SPEED);

	this->configuration = !configuration ? CONFIGURATION_DEFAULT : configuration;
	this->speed         = !eepromSpeed ? SPEED_DEFAULT : eepromSpeed;

	update();
}

/**
 * @brief Returns battery level in percentage based on a 10-bit ADC read.
 *
 * @return uint8_t as the battery level (0-100)
 */
uint8_t Robot::getBatteryLevel(void)
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
int Robot::serializeForRequest(char* buffer)
{
	return sprintf(buffer, "%02x%02x%02x", configuration, speed, getBatteryLevel());
}
