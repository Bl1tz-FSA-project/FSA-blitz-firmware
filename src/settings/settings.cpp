#include "settings.h"
//#include "settings.h"

Config setting = {"1.0", 868.0, 928.0, false};

void setFrequency(float minFreq, float maxFreq)
{
    setting.minHz = minFreq;
    setting.maxHz = maxFreq;
}

void setLoudMode(bool lMode)
{
    setting.loudMode = lMode;
}
