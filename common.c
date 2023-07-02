#include <lgpio.h>

void build_wave(int command, lgPulse_t pulses[])
{
  for (int i=0; i<12; i++)
  {
    int offset = (1 + i) * 2 + 1;

    if ((command & 2048) != 0) {
      pulses[offset].delay = 2000;
    } else {
      pulses[offset].delay = 1000;
    }
  }
}
