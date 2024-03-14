#include "buttons/handlers.h"
#include "backend/scanner.h"
#include "frontend/displayCtrl.h"

//#define DATA_SPIFFS 1 to read from filesystem

//TODO: Buttons interaction, menu panel etc,
//      Radio Debug

//variables debug zone

//setup routine runs once
void setup() {
  Serial.begin(115200);
  Serial.flush();
  delay(2000); 
  
  Serial.println("Starting HW init!");
  radio_init();
  initHardware();
  displayStats();
  attachISR();

  delay(1000);
  typeln("", SMALL_TEXT, true, true); //clears the display
}

void testRadio_entropy()
{
  typewrite("LogMode(I)", 0, 0, BIG_TEXT, false, true);
  entropy_analyze();

  if (RADIO_DEBUG) ESP_LOGD("STATUS", "\n_______DATA RECEIVING ENDED______\n");
  log_output_oled(entropyDetections, rssi_spectre);
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