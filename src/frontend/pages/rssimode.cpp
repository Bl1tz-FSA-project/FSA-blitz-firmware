#include "rssimode.h"

#define NUM_COLUMN      64
#define BATTERY_HEIGHT  10
#define MAX_RSSI        -20
#define MIN_RSSI        -100
#define DBM_VALUE       1.25
#define BOT_MARGIN      9

void drawRSSI(const int RSSIvalues[NUM_COLUMN])
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 57);
    display.println(setting.minHz);
    display.setCursor(98, 57);
    display.println(setting.maxHz);
  
    int maxStartHeight = BATTERY_HEIGHT;
    int maxActualHeight = 64 - BATTERY_HEIGHT - BOT_MARGIN;
    // i dont know for sure what data type is rssi!!!!!
    for(int i = 0; i < NUM_COLUMN; i++)
    {
      int RSSIvalue = RSSIvalues[i];
      int actualHeight = ((MAX_RSSI-MIN_RSSI) - (MAX_RSSI - RSSIvalue)) * DBM_VALUE / 100 * maxActualHeight;
      int startHeight = BATTERY_HEIGHT + maxActualHeight - actualHeight; 
      display.drawFastVLine(i* 2, startHeight, actualHeight, WHITE);
    }
    
    display.display();
}