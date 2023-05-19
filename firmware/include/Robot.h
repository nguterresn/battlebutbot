#include <Arduino.h>
#include <EEPROM.h>
#include "MachineRoom.h"

#define ENABLE_CONSOLE_TEXT          0x01
#define ENABLE_FEEDBACK_LED          0x02
#define ENABLE_SERVO                 0x04

#define EEPROM_SIZE                  1
#define EEPROM_CONFIGURATION_ADDRESS 0x00

class Robot {
public:
	Robot(uint8_t leftMotorIN1, uint8_t leftMotorIN2, uint8_t rightMotorIN1, uint8_t rightMotorIN2, uint8_t feedbackLed, Stream* serial = nullptr);
	void update();
	void connect();
	uint8_t loadConfiguration();
	void saveConfiguration(int configuration);
	uint8_t isConsoleEnabled();
	uint8_t isFeedbackLedEnabled();
	uint8_t isServoEnabled();

	MachineRoom oMachineRoom;
private:
	Stream* serial;
	uint8_t configuration = 0;
	uint8_t ledPin;
};
