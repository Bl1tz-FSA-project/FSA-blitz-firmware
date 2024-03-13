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

    //debug output!
    // highly recommended to use special macros from init.h
    typewrite("TFS BOOT", NEWLINE_X, HEADER_Y, BIG_TEXT, false, false);
    typeln("radio started", SMALL_TEXT, false, false);
    typeln("HW started", SMALL_TEXT, false, true);

    delay(2000);

    typewrite("Created by Hacccker", NEWLINE_X, BOTTOM_Y, SMALL_TEXT, true, true);
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
    update = false writes to buffer but not displays
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
            snprintf(out, 32, string, i*0.2+FREQ, d[i], rssi_spectrum[i]);
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