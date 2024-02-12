#include <Arduino.h>
#include <RadioLib.h>

#include "init.h"
#include "entropy.h"
/* CONFIG NEEDED!!!*/
const u_int fRange = (FREQ_MAX - FREQ) * 5;

ICACHE_RAM_ATTR void read_bit(void);

void check(int state, int op);

void radio_init(); 

//void setup();

void log_output(u_int *matches, float *rssi);

void packet_compare(uint8_t packet[], uint8_t old_packet[], u_int &comp, u_int old_size);

void hop_channel(float koef);

u_int compare(int c_freq, uint8_t packets[fRange][BUFFER_MAX], uint8_t old_packets[fRange][BUFFER_MAX], u_int old_size);

void analyzer_scan();

void clear_out();

void analyzer_scan_legacy(void);

void analyzer_debug();

void entropy_test();

//void loop();