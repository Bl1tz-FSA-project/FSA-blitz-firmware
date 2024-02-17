#include <Arduino.h> //optionally
#include "init/init.h"
#include "backend/scanner.h"

//setup routine runs once
void setup() {
  Serial.begin(115200); 
  initHardware();
  radio_init();
}

void testRadio_entropy()
{

  entropy_analyze(RADIO_RELEASE);

  ESP_LOGD("STATUS", "\n_______DATA RECEIVING ENDED______\n");
  log_output(detections, rssi_spectre);
  ESP_LOGD("RSSI", "    Current: %f", rssi);

  delay(1000);
}



// the loop routine runs over and over again forever:
void loop() {
  testRadio_entropy();
  delay(1);        // delay in between reads for stability
}