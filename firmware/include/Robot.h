#include <Arduino.h>
// https://github.com/esp8266/Arduino/tree/master/libraries/EEPROM
#include <EEPROM.h>
#include "MachineRoom.h"

#define ENABLE_CONSOLE_TEXT 0x01
#define ENABLE_FEEDBACK_LED 0x02
#define ENABLE_SERVO        0x04

typedef enum {
	CONFIGURATION,
	SPEED,
	FRICTION,
	CONFIGURATION_SIZE
} configuration;

class Robot {
public:
	Robot(uint8_t leftMotorIN1, uint8_t leftMotorIN2, uint8_t rightMotorIN1, uint8_t rightMotorIN2, uint8_t servoPin, uint8_t feedbackLedPin, Stream* serial = nullptr);
	void update();
	void connect();
	void loadConfiguration(void);
	void saveConfiguration(int configuration, int speed, int friction);
	uint8_t isConsoleEnabled();
	uint8_t isFeedbackLedEnabled();
	uint8_t isServoEnabled();
	uint8_t getBatteryLevel(void);
	int serializeForRequest(char* buffer);

	MachineRoom oMachineRoom;
private:
	Stream* serial;
	uint8_t configuration, speed, friction, ledPin;
};
