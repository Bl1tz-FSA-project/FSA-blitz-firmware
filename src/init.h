#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPIFFS.h>

#include "handlers.h"


//#include "fs/fs.h"
//#include "backend/scanner.h"
//#include "backend/entropy.h"
#include "settings/settings.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C

#define BTN_DOWN GPIO_NUM_7
#define BTN_UP GPIO_NUM_21
#define BTN_SELECT GPIO_NUM_20

//static params
#define DATA 2 
#define CLK 1
#define PINT 0 
#define RESET 3
#define CS 10

//ALL ABOVE MUST BE IN FILE SYSTEM
//SYSTEM OPTIONS
#define PREAMBLE_LEN 32
#define TRIGGER_MATCH 10 //bytes must match to trigger packet event

//RADIO OPTIONS
#define LISTEN_MS 100
#define FREQ 915.0
#define FREQ_MAX 917.0 //new
#define BITRATE 50.0
#define DEVIATION 25.0
#define RXBW 220.0
#define STEP 0.2//RXBW / 100
#define PWR 5.0
#define RSSI_TRESHOLD -80.0


extern Adafruit_SSD1306 display;

void initHardware();
