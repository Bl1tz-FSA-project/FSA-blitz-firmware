/*
*  Firmware for UAV detection device
*  Created by @SamcraftSam
*  Licence: MIT
*/


#include "hw/setup_libs.h"

//setup routine runs once
void setup() {
  Serial.begin(115200);
  Serial.flush();
  delay(1000); 
  
  Serial.println("Starting HW init!");
  radio_init();
  initHardware();
  displayStats();
  attachISR();

  delay(100);
  typeln("", SMALL_TEXT, true, true); //clears the display
  display_spectrum();
  //ESP_LOGE("DEBUG", "REMOVE LATER! fRange value: %d", fRange);
}

/*
// the loop routine runs over and over again forever:
void loop() {
  testRadio_entropy();
  delay(1);        // delay in between reads for stability
}*/

void loop() {
  // UI STATE REFRESH
  if (needRefresh)
  {
    refresh_page();
  }

  delay(100);
}