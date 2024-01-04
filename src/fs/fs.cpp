#include "SPIFFS.h"
#include "ArduinoJson.h"
#include "types.h"
#include "settings/settings.h"

const char *filepath = "/settings.json";

// TODO: Function for changing settings in GlobalSettings and in filesystem
// ....

// Saves the configuration to a file
void saveConfiguration(const char *filename, const Config &config)
{
  // Delete existing file, otherwise the configuration is appended to the file
  SPIFFS.remove(filename);

  // Open file for writing
  File file = SPIFFS.open(filename, FILE_WRITE);
  if (!file)
  {
    Serial.println(F("Failed to create file"));
    return;
  }

  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/assistant to compute the capacity.
  StaticJsonDocument<512> doc;

  // Set the values in the document
  doc["version"] = config.version;
  doc["maxHz"] = config.maxHz;
  doc["minHz"] = config.minHz;
  // etc..

  // Serialize JSON to file
  if (serializeJson(doc, file) == 0)
  {
    Serial.println(F("Failed to write to file"));
  }

  // Close the file
  file.close();
}

ArduinoJson::V6213PB2::StaticJsonDocument<512> loadSettings() // const char *filepath
{
  StaticJsonDocument<512> doc;
  File file = SPIFFS.open(filepath);
  if (!file)
  {
    Serial.println("[FS.readFile Error] Failed to open for reading");
    return doc;
  }

  DeserializationError error = deserializeJson(doc, file);
  if (error)
  {
    Serial.println(F("Failed to read file, using default configuration"));
    saveConfiguration(filepath, setting);
  }

  // setting.version = doc['version'] | setting.version;
  setting.version = doc["version"] | setting.version;
  setting.maxHz = doc["maxHz"] | setting.maxHz;
  setting.minHz = doc["minHz"] | setting.minHz;
  //strlcpy(setting.version, doc["version"] | setting.version, sizeof(setting.version));
  Serial.println(F("VALIDATED. Json is valid."));

  file.close();

  return doc;
}

void printFile(const char *filename)
{
  // Open file for reading
  File file = SPIFFS.open(filename);
  if (!file)
  {
    Serial.println(F("Failed to read file"));
    return;
  }

  // Extract each characters by one by one
  while (file.available())
  {
    Serial.print((char)file.read());
  }
  Serial.println();

  // Close the file
  file.close();
}

/*void testFsAll(){
    printFile(filepath);
    saveConfiguration(filepath, config);
    printFile(filepath);
}*/