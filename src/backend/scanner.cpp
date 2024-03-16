#include "scanner.h"

/* Code with basic scanning algorhitms
   Contributor: SamcraftSam
*/


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
    t_rssi = radio.getRSSI(false, true); //second arg set to true

    if (t_rssi > rssi)
      rssi = t_rssi;

    // ESP_LOGD("TIMER-DEBUG", "Time: %d, oldtime: %d, rssi: %f", current_time, last_time+100, rssi);
    sys_delay_ms(LISTEN_INTERVAL);
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
      detections[i] = compare(i, packets, old_packets, old_size);
      // matches[i] = comparator[i];
      // comparator[i] = 0;
    }
    received_flag = false;
    log_output(detections, rssi_spectre);

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
    detections[i] = 0;
}

/*  Entropy scanning function 
  
    DOCUMENTATION  NEEDED

*/
void entropy_analyze()
{
  char t_packets[BUFFER_MAX];
  memset(t_packets, 0, BUFFER_MAX); // fix

  u_int old_size = BUFFER_MAX;
  u_int size;

  float koef = -0.2; 

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

    
    if (received_flag)
    {
      detections[f] = process_entropy(t_packets, RADIO_DEBUG, f); //f only to log
      received_flag != received_flag;
    }
  }
}
