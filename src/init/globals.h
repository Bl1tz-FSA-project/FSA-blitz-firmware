#include "init.h"

//fix c++17 and c++99 uncompatibility
#define inline static

// =================== IMPORTANT RADIO DATA ===================
inline const u_int fRange = (FREQ_MAX - FREQ) * 5;
inline float rssi;
inline uint8_t b;

inline int matches[fRange];
inline float rssi_spectre[fRange];
inline int detections[fRange];
