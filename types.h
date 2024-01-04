// typedef struct ListViewOptions ListViewOptions;
#include <Arduino.h>
#pragma once
struct ListViewOptions
{
    char *name;
    int id;
};

struct Config
{
    String version;
    float minHz;
    float maxHz;
    bool loudMode;
};