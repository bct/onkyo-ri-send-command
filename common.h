// maximum command length is 12 bits
#define ONKYO_MAX_COMMAND 0xfff

#define ONKYO_HEADER_PULSE_COUNT   1 * 2
#define ONKYO_COMMAND_PULSE_COUNT 12 * 2
#define ONKYO_TRAILER_PULSE_COUNT  1 * 2

void onkyo_build_command_pulses(int command, lgPulse_t command_pulses[]);
void onkyo_send_command_pulses(int handle, int gpio, lgPulse_t command_pulses[]);
