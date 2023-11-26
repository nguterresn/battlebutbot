#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "controls.h"
#include "oled.h"
#include "transmitter.h"

static TaskHandle_t oled_handle, transmitter_handle;

void setup()
{
	Serial.begin(115200);
	Serial.println("starting..");

	controls_begin();
	oled_begin();
	transmitter_begin();

	xTaskCreate(oled_loop,
	            "oled_loop",
	            configMINIMAL_STACK_SIZE * 5,
	            NULL,
	            10,
	            &oled_handle);
	xTaskCreate(transmitter_loop,
	            "transmitter_loop",
	            configMINIMAL_STACK_SIZE * 10,
	            NULL,
	            10,
	            &transmitter_handle);
}

void loop()
{
}
