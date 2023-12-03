#include "oled.h"
#include "controls.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int item_selected         = 0;                    // which item in the menu is selected

int item_sel_previous;                            // previous item - used in the menu screen to draw the item before the selected one
int item_sel_next;                                // next item - used in the menu screen to draw next item after the selected one

int current_screen                           = 0; // 0 = menu, 1 = screenshot, 2 = qr

const int NUM_ITEMS                          = 3;  // number of items in the list and also the number of screenshots and screenshots with QR codes (other screens)
const int NUM_ITEMS_A                        = 2;  // number of items in the list and also the number of screenshots and screenshots with QR codes (other screens)
const int MAX_ITEM_LENGTH                    = 20; // number of items in the list and also the number of screenshots and screenshots with QR codes (other screens)

char menu_items[NUM_ITEMS] [MAX_ITEM_LENGTH] = {   // array with item names
	{ "Connect Robot" },
	{ "Settings"      },
	{ "Dashboard"     },
};

void show_boot(void);

void oled_begin()
{
	if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
		Serial.println(F("SSD1306 allocation failed"));
		for (;;) {
			; // Don't proceed, loop forever
		}
	}

	show_boot();
}

void oled_loop(void* v)
{
	(void)v;
	for (;;) {
		if (current_screen == 0) {
			continue;
		}
		if (right_pressed()) {
			item_selected++;
			if (item_selected > 2) {
				item_selected = 0;
			}
		}
		if (left_pressed()) {
			item_selected--;
			if (item_selected < 0) {
				item_selected = 2;
			}
		}
		if (select_pressed()) {
		}

		if (current_screen == 1) {
			display.clearDisplay();
			// selected item background
			display.drawBitmap(1, 0, epd_bitmap__border, 123, 32, WHITE);
			// draw selected item
			// display.setFont();
			display.setTextSize(1);   // Draw 2X-scale text
			display.setTextColor(SSD1306_WHITE);
			display.setCursor(25, 32-11);
			display.println(F(menu_items[item_selected]));
			// draw scrollbar background
			display.drawBitmap(128 - 3, 1, epd_bitmap__wheels, 1, 29, WHITE);
			// draw scrollbar handle
			display.drawBitmap(125, 32 / NUM_ITEMS * item_selected, epd_bitmap__selectwheel, 3, 7, WHITE);
			display.display();
		}

		// display.setFont();

		// display.clearDisplay();
		// display.drawBitmap(0, 0, bbb_logo, 128, 32, WHITE);
		// display.display();
		// vTaskDelay(1000 / portTICK_RATE_MS);
		// display.clearDisplay();
		// display.drawBitmap(0, 5, bbb_logo, 128, 32, WHITE);
		// display.display();
		// vTaskDelay(1000 / portTICK_RATE_MS);
		vTaskDelay(100 / portTICK_RATE_MS);
	}
}

void show_boot()
{
	display.clearDisplay();
	display.drawBitmap(0, 0, bbb_logo, 128, 32, WHITE);
	display.display();
	vTaskDelay(2000 / portTICK_RATE_MS);
	current_screen = 1;
}
