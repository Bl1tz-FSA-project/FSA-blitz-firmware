/* 
    FROM THE EARLIEST VERSION OF PROJECT
    Created by: Vladislav @shumdeveloper
    Currently maintained by: @SamcraftSam

*/

#include <Arduino.h>
#pragma once
struct ListViewOptions
{
    char *name;
    int id;
};

// may return to this soon
struct Config
{
    String version;
    float minHz;
    float maxHz;
    bool loudMode;
};