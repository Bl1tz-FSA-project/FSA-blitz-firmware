#include "handlers.h"

void attachISR()
{
	attachInterrupt(digitalPinToInterrupt(BTN_DOWN), handleDownBtn, FALLING);
	attachInterrupt(digitalPinToInterrupt(BTN_UP), handleUpBtn, FALLING);
	attachInterrupt(digitalPinToInterrupt(BTN_SELECT), handleSelectBtn, FALLING);
}

/* =========== BUTTONS HANDLER MODULE ===========

    FROM THE EARLY VERSION OF THE PROJECT

    Created by: Vladislav @shumdeveloper

    Currently maintained by: @SamcraftSam

*/

void handleSelect()
{
    // USING BY INTERRUPTS

    if (page == PAGE_2)
    {
        if (listSelectedIdx == 0)
        {
            // RSI MODE
            page = PAGE_1;
            needRefresh = true;
        }
        else if (listFirstVisibleIdx == 1)
        {
            // SYNC PAGE
            page = PAGE_3;
            needRefresh = true;
        }
        else if (listFirstVisibleIdx == 2)
        {
            // Settings page
            page = PAGE_4;
            needRefresh = true;
        }
        else if (listFirstVisibleIdx == 3)
        {
            // Todo: Update ...
        }
    }
    else if (page == PAGE_3)
    {
        // TODO: Sync page select options
    }
    else if (page == PAGE_4)
    {
        // Settings Page
        if (listSelectedIdx == 0)
        {
            // TODO: Loud mode enable
        }
        else if (listSelectedIdx == 1)
        {
            // TODO: Toggle Flashlight
        }
        else if (listSelectedIdx == 2)
        {
            // TODO
        }
        else if (listSelectedIdx == 3)
        {
            // TODO
        }
        else if (listSelectedIdx == 4)
        {
            // TODO
        }
        // * TODO: Modes switch here..
        else if (listSelectedIdx == 5)
        {
            // return back
            page = PAGE_2;
            needRefresh = true;
        }
    }
	else if (page == PAGE_1) 
	{
		//exit to the menu
		page = PAGE_2;
		needRefresh = true;
	}
    //todo: show which option LMODE is selected currently
    listFirstVisibleIdx = 0;
    listSelectedIdx = 0;
}

/**========================================================================
 *                             BUTTONS
 *========================================================================**/
static unsigned long last_navbtn_interrupt_time = 0;
static unsigned long last_selectbtn_interrupt_time = 0;

bool bounceCheck(String t)
{
    // t  - type of button; nav or sel;

    unsigned long interrupt_time = millis();

    if (t == "nav")
    {
        if (interrupt_time - last_navbtn_interrupt_time > 200)
        {
            last_navbtn_interrupt_time = interrupt_time;
            return true;
        }
        last_navbtn_interrupt_time = interrupt_time;
    }
    else if (t == "sel")
    {
        if (interrupt_time - last_selectbtn_interrupt_time > 200)
        {
            last_selectbtn_interrupt_time = interrupt_time;
            return true;
        }
        last_selectbtn_interrupt_time = interrupt_time;
    }

    return false;
}

void IRAM_ATTR handleUpBtn()
{
    if (!scrollMode || !bounceCheck("nav"))
    {
        return;
    }

    listFirstVisibleIdx -= 1;
    listSelectedIdx -= 1;

    needRefresh = true;
}

void IRAM_ATTR handleDownBtn()
{
    if (!scrollMode || !bounceCheck("nav"))
    {
        return;
    }

    listFirstVisibleIdx += 1;
    listSelectedIdx += 1;

    needRefresh = true;
}

void IRAM_ATTR handleSelectBtn()
{
    if (!bounceCheck("sel"))
    {
        return;
    }

    // Select mode: handle select. Other pages: open menu
    if (scrollMode)
    {
        handleSelect();
    }
    else
    {
        page = PAGE_2;
        needRefresh = true;
    }
}
