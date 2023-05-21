#include "Robot.h"

Robot::Robot(uint8_t leftMotorIN1,
             uint8_t leftMotorIN2,
             uint8_t rightMotorIN1,
             uint8_t rightMotorIN2,
             uint8_t feedbackLed,
             Stream* serial) :
	oMachineRoom(leftMotorIN1, leftMotorIN2, rightMotorIN1, rightMotorIN2),
	serial(serial)
{
	ledPin = feedbackLed;
	pinMode(ledPin, OUTPUT);
	EEPROM.begin(EEPROM_SIZE);

	loadConfiguration();
}

/// @brief Update capabilities according to the configuration saved on the EEPROM
void Robot::update()
{
	digitalWrite(ledPin, isFeedbackLedEnabled());

	oMachineRoom.changeSpeed(this->speed);
	oMachineRoom.changeFriction(this->friction);
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

uint8_t Robot::isFeedbackLedEnabled()
{
	return configuration && ENABLE_FEEDBACK_LED;
}

/// @brief Save new configuration on the EEPROM
/// @param configuration as a byte
void Robot::saveConfiguration(int configuration, int speed, int friction)
{
	// Confirm all of them are the same and return.
	if (this->configuration == configuration &&
	    this->speed == speed &&
	    this->friction == friction) {
		return;
	}
	// Save on EEPROM
	EEPROM.put(CONFIGURATION, (uint8_t)configuration);
	EEPROM.put(SPEED, (uint8_t)speed);
	EEPROM.put(FRICTION, (uint8_t)friction);
	EEPROM.commit();
	// Save on RAM
	this->configuration = configuration;
	this->speed         = speed;
	this->friction      = friction;

	update();
}

void Robot::loadConfiguration(void)
{
	this->configuration = EEPROM.read(CONFIGURATION);
	uint8_t eepromSpeed    = EEPROM.read(SPEED);
	this->speed         = !eepromSpeed ? SPEED_DEFAULT : eepromSpeed;
	uint8_t eepromFriction = EEPROM.read(FRICTION);
	this->friction      = !eepromFriction ? FRICTION_DEFAULT : eepromFriction;

	update();
}
