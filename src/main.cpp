#include <Arduino.h>
#include "hardware.h"
#include "fs/fs.h"
#include "frontend/ui.h"
#include "settings/settings.h"

void setup() {
  Serial.begin(115200);
  initHardware();

/*  setting.version = "14.88";
  saveConfiguration("/settings.json", setting);

  delay(200);
  setting.version = "1.0";*/
  loadSettings();
  
  //printFile("/settings.json"); FOR SERIAL
  // Display First Page
  display.clearDisplay();
 // display_error(setting.version); // dEBUG ONLY
  display_mode_menu(); 

  delay(200);
}

void loop() {
  // UI STATE REFRESH
  if (needRefresh)
  {
    refresh_page();
  }

  delay(200);
}