#include "hardware.h"
#include "types.h"

int listSelectedIdx = 0;
int listFirstVisibleIdx = 0;

const int listScale = 18;

void scrollCheck(ListViewOptions items[], int len)
{
    if (listSelectedIdx >= len)
    {
        listSelectedIdx = 0;
        listFirstVisibleIdx = 0;
    }

    if (listFirstVisibleIdx < 0 || listFirstVisibleIdx > len)
    {
        listSelectedIdx = 0;
        listFirstVisibleIdx = 0;
    }
}

void showList(ListViewOptions items[], int len) // const char *items[]
{
    display.clearDisplay();
    display.setTextSize(1);

    scrollCheck(items, len);

    int firstVisibleIdx = listFirstVisibleIdx;
    int selectedIdx = listSelectedIdx;

    for (int i = firstVisibleIdx; i < len; i++)
    {
        if (i - firstVisibleIdx == selectedIdx - firstVisibleIdx)
        {
            // Highlight the selected item with a filled box
            display.fillRect(0, (i - firstVisibleIdx) * listScale, SCREEN_WIDTH, listScale, SSD1306_WHITE);
            display.setTextColor(SSD1306_BLACK);
            display.setCursor(5, (i - firstVisibleIdx) * listScale + 4);
            display.println(items[i].name);
        }
        else
        {
            // Draw an empty box around non-selected items
            display.drawRect(0, (i - firstVisibleIdx) * listScale, SCREEN_WIDTH, listScale, SSD1306_WHITE);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(5, (i - firstVisibleIdx) * listScale + 4);
            display.println(items[i].name);
        }
    }

    display.display();
}