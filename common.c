#include <lgpio.h>

#include "common.h"

const lgPulse_t ONKYO_PULSE_HEADER[2] = {
  {1, -1, 3000},
  {0, -1, 1000},
};

const lgPulse_t ONKYO_PULSE_TRAILER[2] = {
  {1, -1, 1000},
  {0, -1, 40000},
};

void onkyo_build_command_pulses(int command, lgPulse_t command_pulses[]) {
  for (int i=0; i<ONKYO_COMMAND_PULSE_COUNT; i+=2) {
    int64_t zero_width = (command & 0x800) ? 2000 : 1000;

    command_pulses[i]   = (lgPulse_t) { .bits = 1, .mask = -1, .delay = 1000 };
    command_pulses[i+1] = (lgPulse_t) { .bits = 0, .mask = -1, .delay = zero_width };

    command <<= 1;
  }
}

void onkyo_send_command_pulses(int handle, int gpio, lgPulse_t command_pulses[]) {
  lgTxWave(handle, gpio, ONKYO_HEADER_PULSE_COUNT,  (lgPulse_t*) ONKYO_PULSE_HEADER);
  lgTxWave(handle, gpio, ONKYO_COMMAND_PULSE_COUNT, command_pulses);
  lgTxWave(handle, gpio, ONKYO_TRAILER_PULSE_COUNT, (lgPulse_t*) ONKYO_PULSE_TRAILER);

  while (lgTxBusy(handle, gpio, LG_TX_WAVE)) lguSleep(0.01);
}
