#ifndef HANDLERS_H
#define HANDLERS_H

#include "hw/hardware.h"
#include "frontend/ui_render.h"
#include "frontend/displayCtrl.h"


extern volatile bool DPressed;
extern volatile bool UPressed;
extern volatile bool SPressed;

void attachISR();

IRAM_ATTR void handleDownBtn();

IRAM_ATTR void handleUpBtn();

IRAM_ATTR void handleSelectBtn();


/* =========== BUTTONS HANDLER MODULE ===========

    FROM THE EARLIEST VERSION OF PROJECT

    Created by: Vladislav @shumdeveloper

    Currently maintained by: @SamcraftSam

*/
void handleSelect();
bool bounceCheck(String t);

#endif