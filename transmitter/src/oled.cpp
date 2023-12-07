#include "oled.h"
#include "controls.h"
#include "fonts.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool has_updated  = false;

int item_selected = 0;                             // which item in the menu is selected

int item_sel_previous;                             // previous item - used in the menu screen to draw the item before the selected one
int item_sel_next;                                 // next item - used in the menu screen to draw next item after the selected one

int current_screen                   = 0;          // 0 = menu, 1 = screenshot, 2 = qr

const int NUM_ITEMS                  = 4;          // number of items in the list and also the number of screenshots and screenshots with QR codes (other screens)
const int NUM_ITEMS_A                = 3;
const int MAX_ITEM_LENGTH            = 20;         // number of items in the list and also the number of screenshots and screenshots with QR codes (other screens)

const unsigned char* bitmap_icons[4] = {
	epd_bitmap__cat_icon,
	epd_bitmap__ghost_icon,
	epd_bitmap__schroom_icon,
	epd_bitmap__standcat_icon
};

char menu_items[NUM_ITEMS] [MAX_ITEM_LENGTH] = {   // array with item names
	{ "Connect"  },
	{ "Settings" },
	{ "Test"     },
	{ "Test 2"   },
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
	display.setTextSize(1);
	display.setTextColor(SSD1306_WHITE);
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
			has_updated = false;
			item_selected++;
			if (item_selected > NUM_ITEMS_A) {
				item_selected = 0;
			}
		}
		if (left_pressed()) {
			has_updated = false;
			item_selected--;
			if (item_selected < 0) {
				item_selected = NUM_ITEMS_A;
			}
		}
		if (select_pressed()) {
		}

		// set correct values for the previous and next items
		item_sel_previous = item_selected - 1;
		if (item_sel_previous < 0) {
			item_sel_previous = NUM_ITEMS - 1;
		} // previous item would be below first = make it the last
		item_sel_next = item_selected + 1;
		if (item_sel_next >= NUM_ITEMS) {
			item_sel_next = 0;
		} // next item would be after last = make it the first



		if (current_screen == 1 && !has_updated) {
			has_updated = true;
			display.clearDisplay();
			// selected item background
			display.drawBitmap(0, 22, epd_bitmap__border, 124, 21, WHITE);
			// draw prev selected item and icon
			// display.setFont();
			display.setFont(&FreeMono9pt7b);
			display.setCursor(25, 15 - 0);
			display.println(F(menu_items[item_sel_previous]));
			display.drawBitmap(4, 2, bitmap_icons[item_sel_previous], 16, 16, WHITE);

			// draw selected item and icon
			display.setFont(&FreeMonoBold9pt7b);
			display.setCursor(25, 15 + 20 + 2 - 0);
			display.println(F(menu_items[item_selected]));
			display.drawBitmap(4, 24, bitmap_icons[item_selected], 16, 16, WHITE);

			// draw next item and icon
			display.setFont(&FreeMono9pt7b);
			display.setCursor(25, 15 + 20 + 20 + 2 - 0);
			display.println(F(menu_items[item_sel_next]));
			display.drawBitmap(4, 46, bitmap_icons[item_sel_next], 16, 16, WHITE);

			// draw scrollbar background
			display.drawBitmap(128 - 4, 0, epd_bitmap__selection_dots, 4, 64, WHITE);
			// draw scrollbar handle
			display.drawBitmap(125, 64 / NUM_ITEMS * item_selected, epd_bitmap__selection_bar, 3, 7, WHITE);
			display.display();
		}
		vTaskDelay(100 / portTICK_RATE_MS);
	}
}

void show_boot()
{
	display.clearDisplay();
	display.drawBitmap(0, 0, bbb_logo, 128, 64, WHITE);
	display.display();
	vTaskDelay(2000 / portTICK_RATE_MS);
	current_screen = 1;
}
