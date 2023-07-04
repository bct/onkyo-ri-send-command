## How to run

This will send the command `0x4` followed by the command `0x20`.

    ./onkyo-ri-send-command 0 26 0x4 0x20

The first argument is the number of a gpiochip device. The second argument is the number of a GPIO line. Both can be found in the output of `gpioinfo`. On a Raspberry Pi 3B chip 0 / line 26 is `GPIO26`.

## How to build

    nix-shell
    make

## Onkyo A-9010 RI codes

      0x4    Toggle power
     0x20    Line 1
     0xd9    Power on
     0xda    Power off
     0xe0    Line 3
    0x170    Line 2
    0x203    Volume up
    0x303    Volume down
