#include <Arduino.h>
#include <RadioLib.h>

#include "entropy.h"

/* CONFIG NEEDED!!!*/

//static params
#define DATA 2 
#define CLK 1
#define PINT 0 
#define RESET 3
#define CS 10

//ALL ABOVE MUST BE IN FILE SYSTEM
//SYSTEM OPTIONS
#define PREAMBLE_LEN 32
#define TRIGGER_MATCH 10 //bytes must match to trigger packet event
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE

//RADIO OPTIONS
#define LISTEN_MS 100
#define FREQ 915.0
#define FREQ_MAX 917.0 //new
#define BITRATE 50.0
#define DEVIATION 25.0
#define RXBW 220.0
#define STEP 0.2//RXBW / 100
#define PWR 5.0
#define RSSI_TRESHOLD -80.0

const u_int fRange = (FREQ_MAX - FREQ) * 5;

ICACHE_RAM_ATTR void read_bit(void);

void check(int state, int op);

void radio_init(); 

//void setup();

void log_output(u_int *matches, float *rssi);

void packet_compare(uint8_t packet[], uint8_t old_packet[], u_int &comp, u_int old_size);

void hop_channel(float koef);

u_int compare(int c_freq, uint8_t packets[fRange][BUFFER_MAX],
              uint8_t old_packets[fRange][BUFFER_MAX], u_int old_size);

void analyzer_scan();

void clear_out();

void analyzer_scan_legacy(void);

void analyzer_debug();

void entropy_test();

//void loop();