#include "buttons/handlers.h"
#include "backend/scanner.h"
#include "frontend/displayCtrl.h"


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

  delay(1000);
  typeln("", SMALL_TEXT, true, true); //clears the display

  //ESP_LOGE("DEBUG", "REMOVE LATER! fRange value: %d", fRange);
}

void testRadio_entropy()
{
  typewrite("LogMode(I)", 0, 0, BIG_TEXT, false, true);
  entropy_analyze();
  if (RADIO_DEBUG) ESP_LOGD("STATUS", "_______DATA RECEIVING ENDED______\n");
  
  log_output_oled(detections, rssi_spectre);
  if (RADIO_DEBUG) ESP_LOGD("RSSI", "    Current: %f", rssi);

  delay(10);
}

void scanRadio_entropy()
{
  entropy_analyze();
}

// the loop routine runs over and over again forever:
void loop() {
  testRadio_entropy();
  delay(1);        // delay in between reads for stability
}