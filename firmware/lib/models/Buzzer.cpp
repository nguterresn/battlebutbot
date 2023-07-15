#include "Buzzer.h"

/**
 * @brief Construct a new Buzzer:: Buzzer object
 *
 * @param pin as pin of the buzzer
 */
Buzzer::Buzzer(uint8_t pin)
{
	uint32_t frequency = ledcSetup(BUZZER_CHANNEL,
	                               BUZZER_CHANNEL_DEFAULT_FREQUENCY,
	                               BUZZER_CHANNEL_DEFAULT_RESOLUTION);

	if (frequency) {
		ledcAttachPin(pin, BUZZER_CHANNEL);
		ledcWrite(BUZZER_CHANNEL, 0);
	}
	else {
		ESP_LOGE("buzzer_constructor", "Failed to setup LEDC channel!");
	}
}

void Buzzer::beep(void* vParameters)
{
	for (;;) {
		ledcWriteNote(BUZZER_CHANNEL, NOTE_A, 6);
		vTaskDelay(200 / portTICK_RATE_MS);
		ledcWrite(BUZZER_CHANNEL, 0);

		vTaskDelete(NULL);
	}
}
