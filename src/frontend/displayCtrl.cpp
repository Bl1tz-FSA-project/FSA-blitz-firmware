#include "displayCtrl.h"

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
    // highly recommende to use special macros from init.h
    typewrite("TFS started", NEWLINE_X, HEADER_Y, CAPS_TEXT, false, false);
    typeln("radio started", SMALL_TEXT, false, false);
    typeln("HW started", SMALL_TEXT, false, true);

    delay(5000);

    typewrite("Created by Hacccker", NEWLINE_X, BOTTOM_Y, SMALL_TEXT, true, true);
    
    delay(2000);

    typewrite("HEIL IoT", NEWLINE_X, BOTTOM_Y_CAPS, CAPS_TEXT, true, true);
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