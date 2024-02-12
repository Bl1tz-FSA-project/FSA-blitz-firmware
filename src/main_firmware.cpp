#include <Arduino.h>
#include "init.h"
#include "frontend/ui.h"

void setup() {
  Serial.begin(115200);

  Serial.println("System startup....");
  ESP_LOGD("[INIT]", "SYSTEM STARTUP!");

  initHardware();

/*  setting.version = "14.88";
  saveConfiguration("/settings.json", setting);

  delay(200);
  setting.version = "1.0";*/
  

  /* 
   * LOAD CONF TEMPORARY DISABLED 
   * 
   * MAY BE RECONSTRUCTED SOON
   * 
   */
  //loadSettings();
  
  //printFile("/settings.json"); FOR SERIAL
  // Display First Page
  display.clearDisplay();
 // display_error(setting.version); // dEBUG ONLY
  display_mode_menu(); 

  delay(200);
}

void loop() {
  // UI STATE REFRESH
  //if (needRefresh)
  //{
  //  refresh_page();
  //}

  delay(200);
}