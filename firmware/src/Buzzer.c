#include "Buzzer.h"
#include <Arduino.h>
#include "constants/PinList.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void buzzer_init(void)
{
	pinMode(BUZZER, OUTPUT);
}

void buzzer_beep(void* v)
{
	(void)v;
	analogWrite(BUZZER, 512);
	vTaskDelay(200 / portTICK_RATE_MS);
	analogWrite(BUZZER, 0);
}
