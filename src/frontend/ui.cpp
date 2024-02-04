#include "ui.h"
#include "ui_render.h"
#include "init.h"
#include "types.h"

#define RSSI_PAGE 0
#define MODE_PAGE 1
#define SYNCW_PAGE 2
#define SETTINGS_PAGE 3
#define ERROR_PAGE 5

// Global var
int page = 0;
bool needRefresh = false;
bool scrollMode = false;

ListViewOptions mode_choices[] = {
    {"RSSI MODE >", 0},
    {"SYNC MODE >", 1},
    {"SETTINGS >", 2},
    {"UPDATE SYNC DATA", 3},
};


ListViewOptions settings_opts[] = {
    {"LOUD MODE", 0},
    {"TOGGLE FLASHLIGHT", 1},
    {"L MODE 824-870 MHz", 2},
    {"L MODE 902-950 MHz", 3},
    {"L MODE 824-950 MHz", 4},
    {"EXIT", 5},
};

ListViewOptions sync_choices[] = {
    {"SYNC DEMO", 0},
};

void display_rssi()
{
    page = RSSI_PAGE;

    while (page == RSSI_PAGE)
    {
        // drawRSSI();
    }
}

void display_mode_menu()
{
    page = MODE_PAGE;
    scrollMode = true;
    showList(mode_choices, sizeof(mode_choices) / sizeof(mode_choices[0]));
}

void display_sync_menu()
{
    page = SYNCW_PAGE;
    scrollMode = true;
    showList(sync_choices, sizeof(sync_choices) / sizeof(sync_choices[0]));
}

void display_settings()
{
    page = SETTINGS_PAGE;
    scrollMode = true;
    showList(settings_opts, sizeof(settings_opts) / sizeof(settings_opts[0]));
}

void display_error(String text)
{
    scrollMode = false;
    page = ERROR_PAGE;

    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);

    // Display static text
    display.println("ERROR:");
    display.println("");
    display.println(text);
    display.display();
}

void refresh_page()
{
    needRefresh = false;

    if (page == RSSI_PAGE)
    {
        display_rssi();
    }
    else if (page == MODE_PAGE)
    {
        display_mode_menu();
    }
    else if (page == SYNCW_PAGE)
    {
        display_sync_menu();
    }
    else if (page == SETTINGS_PAGE)
    {
        display_settings();
    }
}