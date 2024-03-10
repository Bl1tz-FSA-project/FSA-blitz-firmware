#include "handlers.h"

/* DONT FORGET TO TURN THIS TO THE FALSE STATE AFTER THE ISR*/
volatile bool DPressed;
/* DONT FORGET TO TURN THIS TO THE FALSE STATE AFTER THE ISR*/
volatile bool UPressed;
/* DONT FORGET TO TURN THIS TO THE FALSE STATE AFTER THE ISR*/
volatile bool SPressed;

void attachISR()
{
	attachInterrupt(digitalPinToInterrupt(BTN_DOWN), handleDownBtn, FALLING);
	attachInterrupt(digitalPinToInterrupt(BTN_UP), handleUpBtn, FALLING);
	attachInterrupt(digitalPinToInterrupt(BTN_SELECT), handleSelectBtn, FALLING);
}

void IRAM_ATTR handleDownBtn()
{
	DPressed = true;	
}

void IRAM_ATTR handleUpBtn()
{
	UPressed = true;
}

void IRAM_ATTR handleSelectBtn()
{
	SPressed = true;
}