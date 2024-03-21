#include "backend/scanner.h"
#include "hw/hardware.h"
#include "ui_render.h"
#include "types.h"

/* =================================== 
   ORIGINAL CODE IS CREATED BY:
      @n1llshul & @shumengineer
   CURRENTLY MAINTAINED BY @SamcraftSam
*/

#define RSSI_PAGE 0
#define MODE_PAGE 1
#define SYNCW_PAGE 2
#define SETTINGS_PAGE 3
#define ERROR_PAGE 5

extern volatile int page;
extern volatile bool needRefresh;
extern bool scrollMode;

void refresh_page();
void display_rssi();
void display_settings();
void display_mode_menu();
void display_sync_menu();
void display_error(String text);
/* =================================== */


void displayStats(void);
void setparams(int16_t x, int16_t y, bool color, int16_t fontsize);
void typewrite(char text[], int16_t x, int16_t y, int16_t fontsize, bool clear, bool update);
void typeln(char text[], int16_t fontsize, bool clear, bool update);
void log_output_oled(int *detections, float *rssi_spectrum);