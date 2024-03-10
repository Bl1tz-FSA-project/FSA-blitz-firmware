#include "init.h"

// DISPLAY =========
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// END OF DISPLAY =======

void initHardware()
{
	// Used only once in setup()
	Serial.begin(115200);
	if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
	{ // Address 0x3D for 128x64
		Serial.println(F("SSD1306 allocation failed"));
		for (;;)
			;
	}

	 // FS INIT
	while (!SPIFFS.begin(true)) {
		Serial.println(F("Failed to initialize FS library"));
		delay(1000);
	}

	// Buttons
	pinMode(BTN_DOWN, INPUT_PULLUP);
	pinMode(BTN_UP, INPUT_PULLUP);
	pinMode(BTN_SELECT, INPUT_PULLUP);
}

