#include "init.h"


// DISPLAY =======
#define SSD1306_128_64

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// ? CHANGE DEFINES IN .h FILE !
#define BTN_DOWN GPIO_NUM_7	   // 7 // 20, 21
#define BTN_UP GPIO_NUM_21	   // 20 // 20, 21
#define BTN_SELECT GPIO_NUM_20 // 21 // 20, 21

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// END OF DISPLAY =======

void initHardware()
{
	// Used only once in setup()

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

	attachInterrupt(digitalPinToInterrupt(BTN_DOWN), handleDownBtn, FALLING);
	attachInterrupt(digitalPinToInterrupt(BTN_UP), handleUpBtn, FALLING);
	attachInterrupt(digitalPinToInterrupt(BTN_SELECT), handleSelectBtn, FALLING);
}