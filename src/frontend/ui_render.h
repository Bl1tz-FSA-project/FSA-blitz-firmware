/* =========== UI RENDER MODULE ===========

    FROM THE EARLIEST VERSION OF PROJECT

    Created by: Vladislav @shumdeveloper

    Currently maintained by: @SamcraftSam

*/
#ifndef RENDER_H
#define RENDER_H

#include "types.h"

extern volatile int listSelectedIdx;
extern volatile int listFirstVisibleIdx;

void scrollCheck(ListViewOptions items[], int len);
void showList(ListViewOptions items[], int len);

#endif