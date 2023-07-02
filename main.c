#include <stdio.h>
#include <stdlib.h>

#include <lgpio.h>

int OUT_GPIO = 26; // GPIO26

#define PULSE_COUNT 28

#define LFLAGS 0

int COMMAND = 0x00E9;

lgPulse_t pulses[PULSE_COUNT] = {
  // header
  {1, -1, 3000},
  {0, -1, 1000},

  // command, 12 bits
  // (delays are placeholders that will be filled in below)
  {1, -1, 1000},
  {0, -1, 0},
  {1, -1, 1000},
  {0, -1, 0},
  {1, -1, 1000},
  {0, -1, 0},
  {1, -1, 1000},
  {0, -1, 0},
  {1, -1, 1000},
  {0, -1, 0},
  {1, -1, 1000},
  {0, -1, 0},
  {1, -1, 1000},
  {0, -1, 0},
  {1, -1, 1000},
  {0, -1, 0},
  {1, -1, 1000},
  {0, -1, 0},
  {1, -1, 1000},
  {0, -1, 0},
  {1, -1, 1000},
  {0, -1, 0},
  {1, -1, 1000},
  {0, -1, 0},

  // trailer
  {1, -1, 1000},
  {0, -1, 40000},
};

int main(int argc, char *argv[])
{
  int h;
  double start, end;
  int total = 0;

  // construct the command wave
  for (int i=0; i<12; i++)
  {
    int offset = 2 + 2*i + 1;

    if ((COMMAND & 2048) != 0) {
      pulses[offset].delay = 2000;
    } else {
      pulses[offset].delay = 1000;
    }
  }

  h = lgGpiochipOpen(0);

  if (h >= 0)
  {
    if (lgGpioClaimOutput(h, LFLAGS, OUT_GPIO, 0) == LG_OKAY)
    {
      lgTxWave(h, OUT_GPIO, PULSE_COUNT, pulses);

      start = lguTime();

      while (lgTxBusy(h, OUT_GPIO, LG_TX_WAVE)) lguSleep(0.01);

      end = lguTime();

      printf("%d pulses took %.1f seconds (exp=%.1f)\n",
          PULSE_COUNT, end-start, total/1e6);
    }

    lgGpiochipClose(h);
  }
}
