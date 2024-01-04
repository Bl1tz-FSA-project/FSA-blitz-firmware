#include<Arduino.h>
#include "hardware.h"

#define NUM_COLUMN      64
#define BATTERY_HEIGHT  10
//#define FREQ_STEP       0.40625
#define MAX_RSSI        -20
#define MIN_RSSI        -100
#define DBM_VALUE       1.25
#define BOT_MARGIN      9

void drawRSSI(const int RSSIvalues[NUM_COLUMN]);
