#include <Arduino.h>
#include <RadioLib.h>

#include "init/init.h"
#include "entropy.h"


#ifndef SCANNER_H
#define SCANNER_H

// =================== IMPORTANT RADIO DATA ===================
//extern const u_int fRange = (FREQ_MAX - FREQ) * 5;
extern float rssi;
extern uint8_t b;


extern int matches[fRange];
extern float rssi_spectre[fRange];
extern int entropyDetections[fRange];

ICACHE_RAM_ATTR void read_bit(void);

void check(int state, int op);

void radio_init(); 

void log_output(int *matches, float *rssi);

void packet_compare(uint8_t packet[], uint8_t old_packet[], u_int &comp, u_int old_size);

void hop_channel(float koef);

u_int compare(int c_freq, uint8_t packets[fRange][BUFFER_MAX], uint8_t old_packets[fRange][BUFFER_MAX], u_int old_size);

void analyzer_scan();

void clear_out();

void entropy_analyze(bool debug);

#endif