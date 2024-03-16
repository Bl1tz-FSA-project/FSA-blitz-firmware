#include <Arduino.h>
#include <RadioLib.h>

#include "init/init.h"
#include "entropy.h"


#ifndef SCANNER_H
#define SCANNER_H

void packet_compare(uint8_t packet[], uint8_t old_packet[], u_int &comp, u_int old_size);

void hop_channel(float koef);

u_int compare(int c_freq, uint8_t packets[fRange][BUFFER_MAX], uint8_t old_packets[fRange][BUFFER_MAX], u_int old_size);

void analyzer_scan();

void clear_out();

void entropy_analyze();

#endif