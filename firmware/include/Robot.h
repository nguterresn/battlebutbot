#include <Arduino.h>
// https://github.com/esp8266/Arduino/tree/master/libraries/EEPROM
#include <EEPROM.h>
#include "MachineRoom.h"

class Robot {
public:
	Robot();
	void update(void);
	void connect(void);
	void loadConfiguration(void);
	void saveConfiguration(int configuration, int speed);
	uint8_t getBatteryLevel(void);
	int serializeForRequest(char* buffer);

	MachineRoom oMachineRoom;
private:
	uint8_t configuration, speed;
};
