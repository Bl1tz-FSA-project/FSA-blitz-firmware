#ifndef INCLUDE_H
#define INCLUDE_H

#include <Arduino.h>
#include <RadioLib.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <SPIFFS.h>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cmath>
#include "esp_log.h"

#define SSD1306_128_64  // initialize serial communication at 9600 bits per second:

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

//display module params
#define BOTTOM_Y 55
#define BOTTOM_Y_CAPS 50
#define HEADER_Y 0
#define NEWLINE_X 0
#define SMALL_TEXT 1
#define BIG_TEXT 2


// ? CHANGE DEFINES IN .h FILE !
#define BTN_DOWN GPIO_NUM_7	   // 7 // 20, 21
#define BTN_UP GPIO_NUM_21	   // 20 // 20, 21
#define BTN_SELECT GPIO_NUM_20 // 21 // 20, 21

//static params
#define DATA 2 
#define CLK 1
#define PINT 0 
#define RESET 3
#define CS 10


#ifndef DATA_SPIFFS
//ALL ABOVE MUST BE IN FILE SYSTEM
//SYSTEM OPTIONS
#define PREAMBLE_LEN 32
#define TRIGGER_MATCH 10 //bytes must match to trigger packet event

/* =========RADIO OPTIONS==========
 *  For LoRa mode: configure according to documentation, 
 *  chip have some restrictions
 *
 */
#define LISTEN_MS 100
#define LISTEN_INTERVAL 10
#define FREQ 915.0
#define FREQ_MAX 930.0 
#define BITRATE 50.0
#define DEVIATION 25.0
#define RXBW 125.0
#define STEP RXBW / 100.0 // test with this
#define PWR 5.0
#define RSSI_TRESHOLD -80.0

#define fRange (u_int)((FREQ_MAX - FREQ)*5)

#endif

// =================== RADIO DATA ===================
extern float rssi;
extern uint8_t b;
extern float rssi_spectre[fRange];
extern int detections[fRange];

// =================== OP Modes & Menu ==============
//set to 1 to use LoRa modulation instead of FSK
#define IS_LORA 0


/* ===== Additional macros ===== */

//debug logging enable:
#define RADIO_DEBUG 1
//release mode:
//#define RADIO_DEBUG 0

extern Adafruit_SSD1306 display;
extern SX1276 radio;


#endif

ICACHE_RAM_ATTR void read_bit(void);

void check(int state, int op);

void radio_init(); 

int radio_fsk();

int radio_lora();

void log_output(int *matches, float *rssi);

void initHardware();
