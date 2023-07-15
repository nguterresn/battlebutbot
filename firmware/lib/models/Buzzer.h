#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp32-hal-ledc.h"
#include "esp_log.h"

#define BUZZER_CHANNEL                    1
#define BUZZER_CHANNEL_DEFAULT_FREQUENCY  10000
#define BUZZER_CHANNEL_DEFAULT_RESOLUTION 12

class Buzzer {
public:
	Buzzer(uint8_t pin);
	static void beep(void* pvParameters);
private:
};
