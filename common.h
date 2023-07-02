// maximum command length is 12 bits
#define ONKYO_MAX_COMMAND 0xfff

// (1 + 12 + 1) * 2
#define ONKYO_PULSE_COUNT 28

#define ONKYO_PULSE_TEMPLATE {\
  /* header */ \
  {1, -1, 3000}, \
  {0, -1, 1000}, \
\
  /* command (12 bits) */ \
  {1, -1, 1000}, \
  {0, -1, 0}, \
  {1, -1, 1000}, \
  {0, -1, 0}, \
  {1, -1, 1000}, \
  {0, -1, 0}, \
  {1, -1, 1000}, \
  {0, -1, 0}, \
  {1, -1, 1000}, \
  {0, -1, 0}, \
  {1, -1, 1000}, \
  {0, -1, 0}, \
  {1, -1, 1000}, \
  {0, -1, 0}, \
  {1, -1, 1000}, \
  {0, -1, 0}, \
  {1, -1, 1000}, \
  {0, -1, 0}, \
  {1, -1, 1000}, \
  {0, -1, 0}, \
  {1, -1, 1000}, \
  {0, -1, 0}, \
  {1, -1, 1000}, \
  {0, -1, 0}, \
\
  /* trailer */ \
  {1, -1, 1000}, \
  {0, -1, 40000}, \
}

void build_wave(int command, lgPulse_t pulses[]);
