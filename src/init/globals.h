/* 
   This file stores global variables
   include only in cpp files
*/

#include "init.h"

//fix c++17 and c++99 uncompatibility
#define inline static

#ifndef GLOBALS_H
#define GLOBALS_H
// =================== IMPORTANT RADIO DATA ===================
inline const u_int fRange = (FREQ_MAX - FREQ) * 5;
inline float rssi;
inline uint8_t b;
inline double avg_entropy;

inline int matches[fRange];
inline float rssi_spectre[fRange];
inline int detections[fRange];

#endif