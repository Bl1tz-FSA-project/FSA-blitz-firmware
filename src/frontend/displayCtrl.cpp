#include "displayCtrl.h"
#include "buttons/handlers.h"

/* This starts the display and prints smth....*/
void displayStats()
{
    display.display();
    delay(2000); // Pause for 2 seconds
    display.clearDisplay();
    display.display();
    delay(2000);

    display.clearDisplay();
    delay(1);
    display.display();
    delay(1);

    typewrite("Created by Hacccker", NEWLINE_X, BOTTOM_Y, SMALL_TEXT, true, true);

    delay(2000);

}


/* sets parameters of the text */
void setparams(int16_t x, int16_t y, bool color, int16_t fontsize)
{
    display.setTextSize(fontsize);
    display.setTextColor(color);
    display.setCursor(x, y);    
}

/* ######################################################
    FAST RE-IMPLEMENTATION OF DELETED FUNCTION! 
    x, y for cursor coords! 
    clear = true to delete everything before typing!
    update = true to display content immidiately
    update = false wr// Global var
    int page = 0;
    bool needRefresh = false;
    bool scrollMode = false;
    ites to buffer but not displays
   ######################################################

   PLS don't spam with display.display()! It loads I2C wire

*/
void typewrite(char text[], int16_t x, int16_t y, int16_t fontsize, bool clear, bool update)
{
    if (clear) display.clearDisplay();

    setparams(x, y, WHITE, fontsize);
    display.println(F(text));

    if (update) display.display(); 
}

/*
    Same function as typewrite, but without coords. 
    Great to display text line-by-line    
*/
void typeln(char text[], int16_t fontsize, bool clear, bool update)
{
    if (clear) display.clearDisplay();

    display.setTextSize(fontsize);
    display.setTextColor(WHITE);
    display.println(F(text));

    if (update) display.display(); 
}

/* This function is used only to display log detections data on the display! */
void log_output_oled(int *d, float *rssi_spectrum)
{
    bool isClear = false;
    typewrite("LogMode(I)", 0, 0, BIG_TEXT, false, true);
    int16_t logStartPosition = display.getCursorY();
    for (u_int i = 0; i < fRange; i++)
    {
        //ESP_LOGV("OUTPUT", "FREQ: %f NUM OF BYTES %d RSSI: %f", i * 0.2 + 915.0, matches[i], rssi[i]);
        if (d[i] > 0)
        //if (true) //debug purposes 
        {
            if (!isClear) typewrite("LogMode( )", 0, 0, BIG_TEXT, true, true), isClear = true;
            char string[] = "%3.1fMHz D:%2d R:%3.1f";
            char out[32];
            snprintf(out, 32, string, i*STEP+FREQ, d[i], rssi_spectrum[i]);
            typeln(out, SMALL_TEXT, false, false);
            if (display.getCursorY() > BOTTOM_Y)
            {
                delay(1000);
                typewrite("LogMode( )", 0, 0, BIG_TEXT, true, true);
            }
        }
    }
    //typewrite("MODE-L (I)", 0, 0, BIG_TEXT, false, true); //--indicate that scanner just saves last info
    display.display();
}


/* ============================================
    Created and contributed
    by N1llShul and Shum.

    Maintained by SamcraftSam
   ============================================
*/

// Global var
volatile int page = 0; //ISR 
volatile bool needRefresh = false;
bool scrollMode = false;


ListViewOptions mode_choices[] = {
    {"FSK MODE >", 0},
    {"LORA MODE >", 1},
    {"SETTINGS[IN DEV] >", 2},
    {"UPDATE SYNC DATA", 3},
};


ListViewOptions settings_opts[] = {
    {"LOUD MODE", 0},
    {"", 1},
    {"L MODE 824-870 MHz", 2},
    {"L MODE 902-950 MHz", 3},
    {"L MODE 824-950 MHz", 4},
    {"EXIT", 5},
};

ListViewOptions sync_choices[] = {
    {"SYNC DEMO", 0},
    {"EXIT", 1},
};

void display_rssi()
{
    page = RSSI_PAGE;

    testRadio_entropy();
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