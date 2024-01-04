#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C

#define BTN_DOWN GPIO_NUM_7
#define BTN_UP GPIO_NUM_21
#define BTN_SELECT GPIO_NUM_2

extern Adafruit_SSD1306 display;

void initHardware();
