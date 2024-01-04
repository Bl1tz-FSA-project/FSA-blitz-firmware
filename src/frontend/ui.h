#include <Arduino.h>

#define RSSI_PAGE 0
#define MODE_PAGE 1
#define SYNCW_PAGE 2
#define SETTINGS_PAGE 3
#define ERROR_PAGE 5

extern int page;
extern bool needRefresh;
extern bool scrollMode;

void refresh_page();
void display_rssi();
void display_settings();
void display_mode_menu();
void display_sync_menu();
void display_error(String text);