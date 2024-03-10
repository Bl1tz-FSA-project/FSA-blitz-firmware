
#include "init/init.h"

void displayStats(void);
void setparams(int16_t x, int16_t y, bool color, int16_t fontsize);
void typewrite(char text[], int16_t x, int16_t y, int16_t fontsize, bool clear, bool update);
void typeln(char text[], int16_t fontsize, bool clear, bool update);
void log_output_oled(int *detections, float *rssi_spectrum);