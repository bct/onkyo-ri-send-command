#include <stdio.h>
#include <stdlib.h>

#include <lgpio.h>

int OUT_GPIO = 26; // GPIO26

// (1 + 12 + 1) * 2
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

void build_wave(int command, lgPulse_t pulses[])
{
  for (int i=0; i<12; i++)
  {
    int offset = (1 + i) * 2 + 1;

    if ((COMMAND & 2048) != 0) {
      pulses[offset].delay = 2000;
    } else {
      pulses[offset].delay = 1000;
    }
  }
}

int main(int argc, char *argv[])
{
  int h;
  int err;

  // construct the command wave
  build_wave(COMMAND, pulses);

  h = lgGpiochipOpen(0);

  if (h < 0)
  {
    printf("opening gpiochip failed: %s (%d)\n", lguErrorText(h), h);
    exit(1);
  }

  if ((err = lgGpioClaimOutput(h, LFLAGS, OUT_GPIO, 0)) != LG_OKAY)
  {
    printf("claiming gpio for output failed: %s (%d)\n", lguErrorText(err), err);
    exit(1);
  }

  lgTxWave(h, OUT_GPIO, PULSE_COUNT, pulses);

  while (lgTxBusy(h, OUT_GPIO, LG_TX_WAVE)) lguSleep(0.01);

  lgGpiochipClose(h);
}
