/* Code with more advanced library
   Cumtributor: SamcraftSam
*/

#include "RadioLib-ESP.h"


// ======================= INTO GLOBAL
bool newline = true; // debug
uint8_t b;           // debug
int count = 0;       // debug too

const u_int fRange = (FREQ_MAX - FREQ) * 5;

u_int matches[fRange];
float rssi_spectre[fRange];
int detections[fRange];

float rssi;

static volatile bool isbusy = false;

// ======================= INTO HARDWARE.H

SX1276 radio = new Module(CS, PINT, RESET, CLK);

// ======================= // END OF HARDWARE.H

// ***
// * INTERRUPTS
/* ISRs, actually only one working properly now */
ICACHE_RAM_ATTR void read_bit(void)
{
  if (!isbusy)
    radio.readBit(DATA);
}

// END OF INTERRUPTS


// debug function to check parameters
void check(int state, int op)
{
  if (state != RADIOLIB_ERR_NONE)
  {
    ESP_LOGE("ERROR", "number: %d, code %d", op, state);
    while (true)
      ;
  }
  else
  {
    ESP_LOGV("SETUP", "NO error on number: %d", op);
  }
}

void radio_init()
{ // BR
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
  // state = radio.setRSSIThreshold(-90.0); may be source of my troubles
  // check(state, 13);
  // state = radio.setDIOPreambleDetect(false); //14, 15 and set DIO0 not working(ignoring input). Low priority TODO
  // check(state, 14);
  // state = radio.setDIOMapping(0, 1);
  // check(state, 15);

  // radio.setDio0Action(func_read, RISING);
  radio.setDirectAction(read_bit);
  sys_delay_ms(1000);
  state = radio.receiveDirect();
  check(state, 16);
}

// setup routine
void setup()
{
  // we dont need this anymore
  Serial.begin(115200);
  delay(1000);
  Serial.println("Serial started!");
  ESP_LOGV("START", "Starting program...");
  Serial.flush();

  // set up radio
  radio_init();
}

/*  MAIN ANALYZER
    Scanning all frequencies, remember unusual packets and compare them.
    TODO: fix bugs in algorithm
*/

// log data in terminal. Debug only.
void log_output(u_int *matches, float *rssi)
{
  for (int i = 0; i < fRange; i++)
  {
    ESP_LOGV("OUTPUT", "FREQ: %f NUM OF BYTES %d RSSI: %f", i * 0.2 + 915.0, matches[i], rssi[i]);
  }
}

// compare 2 arrays
void packet_compare(uint8_t packet[], uint8_t old_packet[], u_int &comp, u_int old_size)
{
  for (int i = 0; i < old_size; i++)
  {
    for (int j = 0; i < old_size; i++)
    {
      if (packet[i] == old_packet[j])
      {
        comp++;
        ESP_LOGD("COMPARATOR", "Comparation! %u", comp);
      }
    }
  }
}

// koef - coef to add to base frequency
void hop_channel(float koef)
{
  int last_time = millis();
  int current_time = millis();

  radio.setFrequency(FREQ + koef);

  // rssi = radio.getRSSI(false, true); //test with FALSE later
  rssi = -130.0;
  // ESP_LOGD("DEBUG", "Current freq: %f RSSI: %f", FREQ + koef, rssi);
  // sys_delay_ms(1000);

  while (current_time < last_time + LISTEN_MS)
  {
    float t_rssi = -127.0;

    int current_time = millis();

    if (current_time - last_time > LISTEN_MS)
    {
      break;
    }
    t_rssi = radio.getRSSI(false, false);

    if (t_rssi > rssi)
      rssi = t_rssi;

    // ESP_LOGD("TIMER-DEBUG", "Time: %d, oldtime: %d, rssi: %f", current_time, last_time+100, rssi);
    sys_delay_ms(10);
  }
  last_time = current_time;
}

// compare old and recent data!
u_int compare(int c_freq, uint8_t packets[fRange][BUFFER_MAX],
              uint8_t old_packets[fRange][BUFFER_MAX], u_int old_size)
{
  u_int comp = 0;
  // comparation of 2-dim array there!
  for (int p_freq = 0; p_freq < fRange; p_freq++)
  {
    for (int c_byte = 0; c_byte < old_size; c_byte++)
    {
      for (int p_byte = 0; p_byte < old_size; p_byte++)
      {
        if (packets[c_freq][c_byte] == old_packets[p_freq][p_byte] &&
            packets[c_freq][c_byte] != 0 && old_packets[p_freq][p_byte] != 0 && packets[c_freq][c_byte] != 0xff && old_packets[p_freq][p_byte] != 0xff)
        {
          comp++;
        }
      }
    };
  }
  return comp;
}

void analyzer_scan()
{
  static uint8_t old_packets[fRange][BUFFER_MAX];
  static uint8_t packets[fRange][BUFFER_MAX];

  u_int old_size = BUFFER_MAX;
  u_int size;
  u_int comparator[fRange];

  float koef;

  bool received_flag = false;

  for (u_int f = 0; f < fRange; f++)
  {
    koef += STEP;
    hop_channel(koef);
    rssi_spectre[f] = rssi;

    // some data retrieved
    if (radio.available() >= 1)
    {
      size = old_size;

      int increment = 0;
      while (radio.available() && increment < BUFFER_MAX)
      {
        b = radio.read();
        // if (rssi >= RSSI_TRESHOLD);
        if (b != 0xff && rssi >= RSSI_TRESHOLD)
        {
          packets[f][increment] = b;
          ESP_LOGE("LIVE", "RSSI: %f FREQ %f SIZE %d DATA %x",
                   rssi, FREQ + koef, increment, packets[f][increment]);
        }
        else
        {
          packets[f][increment] = TERM;
        }
        increment++;
      }

      received_flag = true;
    }
    radio.disableBitSync();
    ets_delay_us(5);
    radio.enableBitSync();
    radio.receiveDirect();
    // isbusy = false;
  }
  // isbusy = true;

  if (received_flag)
  {
    for (int i = 0; i < fRange; i++)
    {
      matches[i] = compare(i, packets, old_packets, old_size);
      // matches[i] = comparator[i];
      // comparator[i] = 0;
    }
    received_flag = false;
    log_output(matches, rssi_spectre);

    // rewrite old cache!
    for (int i = 0; i < fRange; i++)
    {
      for (int j = 0; j < old_size; j++)
      {
        old_packets[i][j] = packets[i][j];
        // packets[i][j] = 0; may be solution but data erases too fast
      }
    }
  }
}

void clear_out()
{
  for (int i = 0; i < fRange; i++)
    matches[i] = 0;
}

// legacy function, cmp only with prev packet received
void analyzer_scan_legacy(void)
{
  static uint8_t old_packet[BUFFER_MAX];
  static uint8_t packet[BUFFER_MAX];

  u_int old_size = BUFFER_MAX;
  u_int size;

  ESP_LOGW("SCAN", "Starting scanner...");
  float koef;

  // start cycle of scanning all frequencies
  for (u_int f = 0; f < fRange; f++)
  {
    koef += STEP;
    u_int comparator = 0;

    hop_channel(koef);

    isbusy = true; // stop reading signals flag

    if (radio.available() < old_size)
    {
      old_size = radio.available();
    }

    if (old_size >= BUFFER_LEN)
    {
      // ESP_LOGD("READING", "Some data retrieved! last rssi = %f", rssi);

      size = old_size;
      while (size)
      {
        packet[size] = radio.read();
        size--;
      }
      // ESP_LOGD("READING", "Reading ended! Comparing...");

      packet_compare(packet, old_packet, comparator, old_size);
      for (int i = 0; i < old_size; i++)
        old_packet[i] = packet[i]; // TODO: CHANGE IT This can owerwrite important packets
    }

    if (comparator > 1)
      rssi_spectre[f] = rssi, matches[f] = comparator;
    else
      matches[f] = 0; // may be possible cause of bugs!!!
    // ESP_LOGD("END", "Cycle ended");

    isbusy = false; // continue listening
  }
}

/*  Debug function for displaying raw data in serial  */
void analyzer_debug()
{

  if (radio.available() >= BUFFER_LEN)
  {

    // radio.standby();
    // sys_delay_ms(10);
    // Serial.println("Outputing buffer: ");
    while (radio.available())
    {
      rssi = radio.getRSSI(false, true);

      if (rssi < RSSI_TRESHOLD)
      {
        newline = false;
        b = radio.read();
        if (b != 0x00 && b != 0xff)
          ;
        Serial.print(b, HEX);
        // Serial.print(" ");
        // Serial.write(b);
        // Serial.print("\t");
        // Serial.print(rssi);
      }
    }
    if (!newline)
    {
      // Serial.println(rssi);
      Serial.println();
      Serial.print(count);
      Serial.print(": ");
      Serial.flush();
      newline = true;
      count++;
      if (count > 100)
      {
        count = 0;
      }
    } // test options
    // radio.disableBitSync();
    // sys_delay_ms(1);
    // radio.enableBitSync();
    // radio.receiveDirect();
  }
}

/* Loop where we can execute all needed functions*/

void entropy_test()
{
  char t_packets[BUFFER_MAX];
  memset(t_packets, 0, BUFFER_MAX); // fix

  u_int old_size = BUFFER_MAX;
  u_int size;

  float koef = -0.2; // WHAAAAT SUPER FIX????

  bool received_flag = false;

  for (u_int f = 0; f < fRange; f++)
  {
    koef += STEP;
    hop_channel(koef);
    rssi_spectre[f] = rssi;

    // some data retrieved
    if (radio.available() >= 1)
    {
      size = old_size;

      int increment = 0;
      while (radio.available() && increment < BUFFER_MAX)
      {
        b = radio.read();

        if (rssi >= RSSI_TRESHOLD)
        {
          t_packets[increment] = b;
        }
        increment++;
      }

      received_flag = true;
    }
    radio.disableBitSync();
    ets_delay_us(5);
    radio.enableBitSync();
    radio.receiveDirect();
    // isbusy = false;

    // ESP_LOGE("LIVE", "RSSI: %f FREQ %f", rssi, FREQ + koef);
    if (received_flag)
    {
      detections[f] = process_entropy(t_packets);
      ESP_LOGD("ENTROPY", "NUM: %d", detections[f]);
      received_flag != received_flag;
    }
  }
}

void loop()
{
  // analyzer_debug();

  // analyzer_scan();
  // clear_out(); //debug
  entropy_test();

  ESP_LOGD("STATUS", "\n_______DATA RECEIVING ENDED______\n");
  ESP_LOGD("RSSI", "    Current: %f", radio.getRSSI(false, false));

  // sys_delay_ms(1000);
}