#include "Robot.h"

Robot::Robot(uint8_t leftMotorIN1,
             uint8_t leftMotorIN2,
             uint8_t rightMotorIN1,
             uint8_t rightMotorIN2,
             uint8_t feedbackLed,
             Stream* serial) :
	oMachineRoom(leftMotorIN1, leftMotorIN2, rightMotorIN1, rightMotorIN2),
	ledPin(feedbackLed),
	serial(serial)
{
	pinMode(ledPin, OUTPUT);
	EEPROM.begin(EEPROM_SIZE);
	this->configuration = loadConfiguration();
}

/// @brief Update capabilities according to the configuration saved on the EEPROM
void Robot::update()
{
	digitalWrite(ledPin, isFeedbackLedEnabled());
}

/// @brief Method feedback when a client connects to the webpage
void Robot::connect()
{
	// Add an LED to show the web control page is open.
	oMachineRoom.brake();
	if (isFeedbackLedEnabled()) {
		digitalWrite(ledPin, HIGH);
	}
}

// uint8_t Robot::isConsoleEnabled()
// {
// 	return configuration && ENABLE_CONSOLE_TEXT;
// }

uint8_t Robot::isFeedbackLedEnabled()
{
	return configuration && ENABLE_FEEDBACK_LED;
}

// uint8_t Robot::isServoEnabled()
// {
// 	return configuration && ENABLE_SERVO;
// }

/// @brief Save new configuration on the EEPROM
/// @param configuration as a byte
void Robot::saveConfiguration(int configuration)
{
	if (this->configuration == configuration) {
		return;
	}
	// Save on EEPROM
	EEPROM.put(EEPROM_CONFIGURATION_ADDRESS, (uint8_t)configuration);
	EEPROM.commit();
	this->configuration = configuration;
	update();
}

uint8_t Robot::loadConfiguration()
{
	this->configuration = EEPROM.read(EEPROM_CONFIGURATION_ADDRESS);
	update();
	return this->configuration;
}
