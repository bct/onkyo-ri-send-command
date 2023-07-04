#include <stdio.h>
#include <stdlib.h>

#include <lgpio.h>

#include "common.h"

int OUT_GPIO = 26; // GPIO26

#define LFLAGS 0

int parse_command(char *command_str) {
  int result;
  char *tail;

  result = strtol(command_str, &tail, 0);

  if (*tail != '\0') {
    printf("\"%s\" is not a valid integer (%s)\n", command_str, tail);
    exit(1);
  }

  if (result < 0 || result > ONKYO_MAX_COMMAND) {
    printf("command %X is outside the expected range (0-%X)\n", result, ONKYO_MAX_COMMAND);
    exit(1);
  }

  return result;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("usage: %s INT_LITERAL\n", argv[0]);
    exit(1);
  }

  int command = parse_command(argv[1]);

  int err;

  // construct the command wave
  lgPulse_t command_pulses[ONKYO_COMMAND_PULSE_COUNT];
  onkyo_build_command_pulses(command, command_pulses);

  int h = lgGpiochipOpen(0);

  if (h < 0) {
    printf("opening gpiochip failed: %s (%d)\n", lguErrorText(h), h);
    exit(1);
  }

  if ((err = lgGpioClaimOutput(h, LFLAGS, OUT_GPIO, 0)) != LG_OKAY) {
    printf("claiming gpio for output failed: %s (%d)\n", lguErrorText(err), err);
    exit(1);
  }

  onkyo_send_command_pulses(h, OUT_GPIO, command_pulses);

  lgGpiochipClose(h);
}
