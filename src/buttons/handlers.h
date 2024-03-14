#ifndef HANDLERS_H
#define HANDLERS_H

#include "init/init.h"

extern volatile bool DPressed;
extern volatile bool UPressed;
extern volatile bool SPressed;

void attachISR();

IRAM_ATTR void handleDownBtn();

IRAM_ATTR void handleUpBtn();

IRAM_ATTR void handleSelectBtn();

#endif