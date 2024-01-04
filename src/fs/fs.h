#include "ArduinoJson.h"
#include "types.h"

ArduinoJson::V6213PB2::StaticJsonDocument<512> loadSettings();
void printFile(const char *filename);
void saveConfiguration(const char *filename, const Config &config);
