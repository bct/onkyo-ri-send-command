#include <stdio.h>
#include <stdlib.h>

#include <lgpio.h>

#include "common.h"

#define LFLAGS 0

int parse_int(char *str, int base) {
  char *tail;
  int result = strtol(str, &tail, base);

  if (*tail != '\0') {
    printf("\"%s\" is not a valid integer (%s)\n", str, tail);
    exit(1);
  }

  return result;
}

int parse_command(char *command_str) {
  // base=0 allows hexadecimal and octal
  int result = parse_int(command_str, 0);

  if (result < 0 || result > ONKYO_MAX_COMMAND) {
    printf("command %X is outside the expected range (0-%X)\n", result, ONKYO_MAX_COMMAND);
    exit(1);
  }

  return result;
}

int main(int argc, char *argv[]) {
  if (argc < 4) {
    printf("usage: %s GPIODEV GPIO COMMAND [COMMAND...]\n", argv[0]);
    exit(1);
  }

  int gpio_dev = parse_int(argv[1], 10);
  int out_gpio = parse_int(argv[2], 10);

  int command_count = argc - 3;
  int commands[command_count];

  for (int i = 0; i < command_count; i++) {
    commands[i] = parse_command(argv[i+3]);
  }

  int err;

  lgPulse_t command_pulses[ONKYO_COMMAND_PULSE_COUNT];

  int h = lgGpiochipOpen(gpio_dev);

  if (h < 0) {
    printf("opening gpiochip failed: %s (%d)\n", lguErrorText(h), h);
    exit(1);
  }

  if ((err = lgGpioClaimOutput(h, LFLAGS, out_gpio, 0)) != LG_OKAY) {
    printf("claiming gpio for output failed: %s (%d)\n", lguErrorText(err), err);
    exit(1);
  }

  for (int i = 0; i < command_count; i++) {
    onkyo_build_command_pulses(commands[i], command_pulses);
    onkyo_send_command_pulses(h, out_gpio, command_pulses);
  }

  lgGpiochipClose(h);
}
