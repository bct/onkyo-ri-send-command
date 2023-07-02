#include <stdio.h>
#include <stdlib.h>

#include <lgpio.h>

#include "common.h"

int OUT_GPIO = 26; // GPIO26

#define LFLAGS 0

lgPulse_t pulses[ONKYO_PULSE_COUNT] = ONKYO_PULSE_TEMPLATE;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("usage: %s INT_LITERAL\n", argv[0]);
    exit(1);
  }

  char *tail;
  int command = strtol(argv[1], &tail, 0);

  if (*tail != '\0') {
    printf("\"%s\" is not a valid integer (%s)\n", argv[1], tail);
    exit(1);
  }

  if (command < 0 || command > ONKYO_MAX_COMMAND) {
    printf("command %X is outside the expected range (0-%X)\n", command, ONKYO_MAX_COMMAND);
    exit(1);
  }

  int err;

  // construct the command wave
  build_wave(command, pulses);

  int h = lgGpiochipOpen(0);

  if (h < 0) {
    printf("opening gpiochip failed: %s (%d)\n", lguErrorText(h), h);
    exit(1);
  }

  if ((err = lgGpioClaimOutput(h, LFLAGS, OUT_GPIO, 0)) != LG_OKAY) {
    printf("claiming gpio for output failed: %s (%d)\n", lguErrorText(err), err);
    exit(1);
  }

  lgTxWave(h, OUT_GPIO, ONKYO_PULSE_COUNT, pulses);

  while (lgTxBusy(h, OUT_GPIO, LG_TX_WAVE)) lguSleep(0.01);

  lgGpiochipClose(h);
}
