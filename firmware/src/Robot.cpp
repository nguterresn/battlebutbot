#include "Robot.h"

/**
 * @brief Construct a new Robot:: Robot object
 *
 * @param leftMotorIN1
 * @param leftMotorIN2
 * @param rightMotorIN1
 * @param rightMotorIN2
 * @param servoPin
 * @param feedbackLedPin
 * @param serial
 */
Robot::Robot(uint8_t leftMotorIN1,
             uint8_t leftMotorIN2,
             uint8_t rightMotorIN1,
             uint8_t rightMotorIN2,
             uint8_t servoPin,
             uint8_t feedbackLedPin,
             Stream* serial) :
	oMachineRoom(leftMotorIN1, leftMotorIN2, rightMotorIN1, rightMotorIN2, servoPin, serial),
	serial(serial)
{
	ledPin = feedbackLedPin;
	pinMode(ledPin, OUTPUT);
	EEPROM.begin(CONFIGURATION_SIZE);

	// Load the configuration as soon as the robot boots.
	loadConfiguration();
}

/**
 * @brief Update capabilities according to the configuration saved on the EEPROM.
 *
 */
void Robot::update()
{
	digitalWrite(ledPin, isFeedbackLedEnabled());

	oMachineRoom.changeSpeed(this->speed);
	oMachineRoom.changeFriction(this->friction);
}

/**
 * @brief Method feedback when a client connects to the webpage
 *
 */
void Robot::connect()
{
	oMachineRoom.reset();
}


/**
 * @brief Checks if the feedback led is enable
 *
 * @return uint8_t
 */
uint8_t Robot::isFeedbackLedEnabled()
{
	return configuration & ENABLE_FEEDBACK_LED;
}

/**
 * @brief Save new configuration on the EEPROM
 *
 * @param configuration as a byte
 * @param speed as a byte
 * @param friction as a byte
 */
void Robot::saveConfiguration(int configuration, int speed, int friction)
{
	// Confirm all of them are the same and return.
	if (this->configuration == configuration &&
	    this->speed == speed &&
	    this->friction == friction) {
		return;
	}
	// Save on EEPROM
	EEPROM.put(CONFIGURATION, configuration);
	EEPROM.put(SPEED, speed);
	EEPROM.put(FRICTION, friction);
	EEPROM.commit();
	// Save on RAM
	this->configuration = configuration;
	this->speed         = speed;
	this->friction      = friction;

	update();
}

/**
 * @brief Load configuration from EEPROM
 *
 */
void Robot::loadConfiguration(void)
{
	this->configuration = EEPROM.read(CONFIGURATION);
	uint8_t eepromSpeed    = EEPROM.read(SPEED);
	this->speed         = !eepromSpeed ? SPEED_DEFAULT : eepromSpeed;
	uint8_t eepromFriction = EEPROM.read(FRICTION);
	this->friction      = !eepromFriction ? FRICTION_DEFAULT : eepromFriction;

	update();
}

/**
 * @brief Returns battery level in percentage based on a 10-bit ADC read.
 *
 * @return uint8_t as the battery level (0-100)
 */
uint8_t Robot::getBatteryLevel(void)
{
	int digitalValueRead = analogRead(A0);

	int level            = 0.3417 * digitalValueRead - 250;

	if (level < 0) {
		return 0;
	}
	return level;
}

/**
 * @brief Serializes the configuration, speed and friction into hex
 *
 * @param buffer of 10 bytes (set on `WebServer.cpp`)
 * @return int
 */
int Robot::serializeForRequest(char* buffer)
{
	return sprintf(buffer, "%02x%02x%02x%02x", configuration, speed, friction, getBatteryLevel());
}
