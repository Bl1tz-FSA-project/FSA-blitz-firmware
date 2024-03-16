#include "init.h"

// DISPLAY =========
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ============= RADIO ==============
float rssi;
uint8_t b;

int matches[fRange];
float rssi_spectre[fRange];
int detections[fRange];

SX1276 radio = new Module(CS, PINT, RESET, CLK);

// ISR to read radio in Continious Mode
ICACHE_RAM_ATTR void read_bit(void)
{
	radio.readBit(DATA);
}

// DEPRECATED! debug function to check parameters
void check(int state, int op)
{
  Serial.println("Radio Setup check!"); // remove later
  if (state != RADIOLIB_ERR_NONE)
  {
    ESP_LOGE("ERROR", "%d, code %d\n", op, state);
    while (true)
      ;
  }
  else
  {
    ESP_LOGV("SETUP", "NO error %d\n", op);
  }
  delay(10);
}

void errorcheck(int code)
{
	ESP_LOGW("CHECK", "%s", "Radio setup check!");

	if (code != RADIOLIB_ERR_NONE)
  	{
    	ESP_LOGE("ERROR", "Code %d, device stopped...\n", code);
    	while (true);
  	}
  	else
  	{
    	ESP_LOGI("SETUP", "NO error, code %d. Continuing boot\n", code);
  	}
}

void radio_init()
{
	int setup_status;
	if (IS_LORA)
	{
		setup_status = radio_lora();
	}
	else
	{
		setup_status = radio_fsk();
	}

	errorcheck(setup_status);
}

//this function must be rewritten
int radio_fsk()
{ 
  delay(10); 
  int state = radio.beginFSK(FREQ, BITRATE, DEVIATION, RXBW, PWR, PREAMBLE_LEN, false);
  check(state, 1);
  state = radio.setCurrentLimit(100);
  check(state, 6);
  state = radio.setDataShaping(RADIOLIB_SHAPING_NONE);
  check(state, 7);
  state = radio.enableBitSync();
  check(state, 9);
  state = radio.setGain(0);
  check(state, 11);
  state = radio.setEncoding(RADIOLIB_ENCODING_NRZ);
  check(state, 12);
  radio.setDirectAction(read_bit);
  //sys_delay_ms(1000);
  state = radio.receiveDirect();
  check(state, 16);

  ESP_LOGE("DEBUG", "Datarate %d", radio.getDataRate());

  return 0;
}


int radio_lora()
{
	delay(10);

	int state = radio.begin(FREQ, RXBW, 9U, RADIOLIB_SX126X_SCAN_INTERVAL_7_68_US, 18U, PWR, PREAMBLE_LEN, 0);
	if (!state != RADIOLIB_ERR_NONE) return state;
	state = radio.setCurrentLimit(100);
	if (!state != RADIOLIB_ERR_NONE) return state;
	state = radio.enableBitSync();
	if (!state != RADIOLIB_ERR_NONE) return state;
	radio.setDirectAction(read_bit);
	state = radio.receiveDirect();
	if (!state != RADIOLIB_ERR_NONE) return state;

}

// log data in terminal. Debug only.
void log_output(int *matches, float *rssi)
{
  for (u_int i = 0; i < fRange; i++)
  {
    ESP_LOGV("OUTPUT", "FREQ: %f NUM OF BYTES %d RSSI: %f", i * 0.2 + 915.0, matches[i], rssi[i]);
  }
}


void initHardware()
{
	// Used only once in setup()
	Serial.begin(115200);
	if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
	{ // Address 0x3D for 128x64
		Serial.println(F("SSD1306 allocation failed"));
		for (;;)
			;
	}

	 // FS INIT
	while (!SPIFFS.begin(true)) {
		Serial.println(F("Failed to initialize FS library"));
		delay(1000);
	}

	// Buttons
	pinMode(BTN_DOWN, INPUT_PULLUP);
	pinMode(BTN_UP, INPUT_PULLUP);
	pinMode(BTN_SELECT, INPUT_PULLUP);
}

